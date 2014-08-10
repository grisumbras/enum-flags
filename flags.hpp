#ifndef ENUM_CLASS_FLAGS_HPP
#define ENUM_CLASS_FLAGS_HPP


#include <initializer_list>
#include <type_traits>
#include <utility>


namespace detail_ {


template <class E, class Enabler = void> struct is_enum_class
    : public std::false_type {};


template <class E>
struct is_enum_class<E, typename std::enable_if<std::is_enum<E>::value>::type>
    : public std::integral_constant<
        bool,
        !std::is_convertible<E, typename std::underlying_type<E>::type>::value>
{};


} // namespace detail_


template <class E, class Enabler = void> struct flags;


template <class E>
struct flags<E,
             typename std::enable_if<detail_::is_enum_class<E>::value>::type> {
public:
    using enum_type = E;
    using underlying_type = typename std::underlying_type<enum_type>::type;

    constexpr flags() : val_{0} {}
#ifdef ENUM_CLASS_FLAGS_FORBID_IMPLICT_CONVERSION
    explicit
#endif
    constexpr flags(enum_type e) : val_{static_cast<underlying_type>(e)} {}
    flags(const flags &fl) = default;
    flags(flags &&fl) = default;
    flags(const std::initializer_list<enum_type> il) : val_{0} {
        for (auto e: il) { val_ |= static_cast<underlying_type>(e); }
    }
    template <class... Args> flags(Args... args) : flags{args...} {}

    flags &operator=(enum_type e) {
        val_ = static_cast<underlying_type>(e);
        return *this;
    }
    flags &operator=(const flags &fl) {
        val_ = fl.val_;
        return *this;
    }
    flags &operator=(flags &&fl) { return *this = fl; }

    constexpr explicit operator bool() const { return val_; }
    constexpr bool operator!() const { return !val_; }

    flags &operator|=(const flags &fl) {
        val_ |= fl.val_;
        return *this;
    }
    flags &operator&=(const flags &fl) {
        val_ &= fl.val_;
        return *this;
    }
    flags &operator^=(const flags &fl) {
        val_ ^= fl.val_;
        return *this;
    }

    flags &operator&=(enum_type e) {
        val_ &= static_cast<underlying_type>(e);
        return *this;
    }
    flags &operator|=(enum_type e) {
        val_ |= static_cast<underlying_type>(e);
        return *this;
    }
    flags &operator^=(enum_type e) {
        val_ &= static_cast<underlying_type>(e);
        return *this;
    }

    flags operator~() { return flags(~val_); }

    void swap(flags &fl) throw() { std::swap(val_, fl.val_); }

    constexpr underlying_type underlying_value() const { return val_; }
    void set_underlying_value(underlying_type newval) { val_ = newval; }

private:
    constexpr flags(underlying_type val) : val_{val} {}

    underlying_type val_;
};


template <class E> flags<E> operator|(flags<E> f1, flags<E> f2) {
    return f1 |= f2;
}


template <class E> flags<E> operator|(flags<E> f, E e) {
    return f |= e;
}


template <class E> flags<E> operator|(E e, flags<E> f) {
    return f |= e;
}


template <class E>
typename std::enable_if<
    std::is_same<E, typename flags<E>::enum_type>::value,
    flags<E>
>::type
operator|(E e1, E e2) { return flags<E>{e1} |= e2; }


template <class E> flags<E> operator&(flags<E> f1, flags<E> f2) {
    return f1 &= f2;
}


template <class E> flags<E> operator&(flags<E> f, E e) {
    return f &= e;
}


template <class E> flags<E> operator&(E e, flags<E> f) {;
    return f &= e;
}

template <class E>
typename std::enable_if<
    std::is_same<E, typename flags<E>::enum_type>::value,
    flags<E>
>::type
operator&(E e1, E e2) { return flags<E>{e1} &= e2; }


template <class E> flags<E> operator^(flags<E> f1, flags<E> f2) {
    return f1 ^= f2;
}


template <class E> flags<E> operator^(flags<E> f, E e) {
    return f ^= e;
}


template <class E> flags<E> operator^(E e, flags<E> f) {
    return f ^= e;
}

template <class E>
typename std::enable_if<
    std::is_same<E, typename flags<E>::enum_type>::value,
    flags<E>
>::type
operator^(E e1, E e2) { return flags<E>{e1} ^= e2; }


template <class E>
bool operator==(const flags<E> &fl1, const flags<E> &fl2) {
    return fl1.underlying_value() == fl2.underlying_value();
}


template <class E>
bool operator!=(const flags<E> &fl1, const flags<E> &fl2) {
    return fl1.underlying_value() != fl2.underlying_value();
}


#endif // ENUM_CLASS_FLAGS_HPP
