#ifndef ENUM_CLASS_FLAGS_HPP
#define ENUM_CLASS_FLAGS_HPP


#include <type_traits>
#include <utility>


template <class E, class Enabler = void> struct flags;


template <class E>
struct flags<E, typename std::enable_if<std::is_enum<E>::value>::type> {
public:
    using enum_type = E;
    using underlying_type = typename std::underlying_type<enum_type>::type;

    flags() : val_{0} {}
#ifdef ENUM_CLASS_FLAGS_FORBID_IMPLICT_CONVERSION
    explicit
#endif
    flags(enum_type e) : val_{static_cast<underlying_type>(e)} {}
    flags(const flags &fl) = default;
    flags(flags &&fl) = default;

    flags &operator=(enum_type e) {
        val_ = static_cast<underlying_type>(e);
        return *this;
    }
    flags &operator=(const flags &fl) {
        val_ = fl.val_;
        return *this;
    }
    flags &operator=(flags &&fl) { return *this = fl; }

    explicit operator bool() const { return val_; }
    bool operator!() const { return !val_; }

    flags &operator|=(flags &fl) {
        val_ |= fl.val_;
        return *this;
    }
    flags &operator&=(flags &fl) {
        val_ &= fl.val_;
        return *this;
    }
    flags &operator^=(flags &fl) {
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

    underlying_type underlying_value() const { return val_; }
    void set_underlying_value(underlying_type newval) { val_ = newval; }

private:
    flags(underlying_type val) : val_{val} {}

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


template <class E> flags<E> operator&(flags<E> f1, flags<E> f2) {
    return f1 &= f2;
}


template <class E> flags<E> operator&(flags<E> f, E e) {
    return f &= e;
}


template <class E> flags<E> operator&(E e, flags<E> f) {;
    return f &= e;
}


template <class E> flags<E> operator^(flags<E> f1, flags<E> f2) {
    return f1 ^= f2;
}


template <class E> flags<E> operator^(flags<E> f, E e) {
    return f ^= e;
}


template <class E> flags<E> operator^(E e, flags<E> f) {
    return f ^= e;
}


#endif // ENUM_CLASS_FLAGS_HPP
