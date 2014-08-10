#ifndef ENUM_CLASS_FLAGS_HPP
#define ENUM_CLASS_FLAGS_HPP


#include <initializer_list>
#include <iterator>
#include <numeric>
#include <type_traits>
#include <utility>


template <class E, class Enabler = void> struct flags;


namespace detail_ {


template <class E, class Enabler = void> struct is_enum_class
    : public std::false_type {};


template <class E>
struct is_enum_class<E, typename std::enable_if<std::is_enum<E>::value>::type>
    : public std::integral_constant<
        bool,
        !std::is_convertible<E, typename std::underlying_type<E>::type>::value>
{};


template <class E> class FlagsEnumIterator;
template <class E> inline bool operator==(const FlagsEnumIterator<E> &i1,
                                          const FlagsEnumIterator<E> &i2
                                         ) noexcept;
template <class E> inline bool operator!=(const FlagsEnumIterator<E> &i1,
                                          const FlagsEnumIterator<E> &i2
                                         ) noexcept;


template <class E>
class FlagsEnumIterator {
    template <class E1, class V> friend class flags;
    friend bool operator==<>(const FlagsEnumIterator<E> &i1,
                             const FlagsEnumIterator<E> &i2) noexcept;
    friend bool operator!=<>(const FlagsEnumIterator<E> &i1,
                             const FlagsEnumIterator<E> &i2) noexcept;

public:
    using difference_type = std::ptrdiff_t;
    using value_type = E;
    using pointer = value_type*;
    using reference = const value_type;
    using iterator_category = std::forward_iterator_tag;

    FlagsEnumIterator() noexcept : mask_{0} {}

    FlagsEnumIterator &operator++() noexcept {
        nextMask();
        return *this;
    }
    FlagsEnumIterator operator++(int) noexcept {
        auto copy = *this;
        ++(*this);
        return copy;
    }

    reference operator*() noexcept { return static_cast<value_type>(mask_); }

private:
    using underlying_type = typename flags<E>::underlying_type;

    FlagsEnumIterator(const flags<E> &fl) noexcept
        : mask_{1}, uvalue_{fl.underlying_value()} {
        if (!(mask_ & uvalue_)) { nextMask(); }
    }

    FlagsEnumIterator(const flags<E> &fl, E e) noexcept
        : uvalue_{fl.underlying_value()}
        , mask_{static_cast<underlying_type>(
            static_cast<underlying_type>(e) & uvalue_)} {}

    void nextMask() noexcept {
        do {
            mask_ <<= 1;
        } while (mask_ && !(mask_ & uvalue_));
    }

    underlying_type uvalue_;
    underlying_type mask_;
};


template <class E> bool operator==(const FlagsEnumIterator<E> &i1,
                                   const FlagsEnumIterator<E> &i2) noexcept {
    return i1.mask_ == i2.mask_;
}


template <class E> bool operator!=(const FlagsEnumIterator<E> &i1,
                                   const FlagsEnumIterator<E> &i2) noexcept {
    return i1.mask_ != i2.mask_;
}


} // namespace detail_


template <class E>
struct flags<E,
             typename std::enable_if<detail_::is_enum_class<E>::value>::type> {
public:
    using enum_type = E;
    using underlying_type = typename std::make_unsigned<
        typename std::underlying_type<enum_type>::type>::type;

    using iterator = detail_::FlagsEnumIterator<E>;
    using const_iterator = iterator;
    using value_type = typename iterator::value_type;
    using reference = typename iterator::reference;
    using const_reference = typename iterator::reference;
    using pointer = enum_type*;
    using const_pointer = const enum_type*;
    using size_type = std::size_t;
    using difference_type = typename iterator::difference_type;

    constexpr flags() noexcept : val_{0} {}
#ifdef ENUM_CLASS_FLAGS_FORBID_IMPLICT_CONVERSION
    explicit
#endif
    constexpr flags(enum_type e) noexcept
        : val_{static_cast<underlying_type>(e)} {}
    flags(const flags &fl) = default;
    flags(flags &&fl) = default;
    flags(const std::initializer_list<enum_type> il) noexcept : val_{0} {
        for (auto e: il) { val_ |= static_cast<underlying_type>(e); }
    }
    template <class... Args>
    flags(enum_type e, Args... args)  noexcept : flags{args...} {
        val_ |= static_cast<underlying_type>(e);
    }

    flags &operator=(enum_type e) noexcept {
        val_ = static_cast<underlying_type>(e);
        return *this;
    }
    flags &operator=(const flags &fl) noexcept {
        val_ = fl.val_;
        return *this;
    }
    flags &operator=(flags &&fl) noexcept { return *this = fl; }

    constexpr explicit operator bool() const noexcept { return val_; }
    constexpr bool operator!() const noexcept { return !val_; }

    flags &operator|=(const flags &fl) noexcept {
        val_ |= fl.val_;
        return *this;
    }
    flags &operator&=(const flags &fl) noexcept {
        val_ &= fl.val_;
        return *this;
    }
    flags &operator^=(const flags &fl) noexcept {
        val_ ^= fl.val_;
        return *this;
    }

    flags &operator&=(enum_type e) noexcept {
        val_ &= static_cast<underlying_type>(e);
        return *this;
    }
    flags &operator|=(enum_type e) noexcept {
        val_ |= static_cast<underlying_type>(e);
        return *this;
    }
    flags &operator^=(enum_type e) noexcept {
        val_ &= static_cast<underlying_type>(e);
        return *this;
    }

    flags operator~() const noexcept { return flags(~val_); }

    void swap(flags &fl) noexcept { std::swap(val_, fl.val_); }

    constexpr underlying_type underlying_value() const noexcept { return val_; }
    void set_underlying_value(underlying_type newval) noexcept {
        val_ = newval;
    }

    bool empty() const noexcept { return !val_; }
    size_type size() const noexcept {
        return std::accumulate(begin(), end(), static_cast<size_type>(0),
                               [](size_type acc, enum_type) { return ++acc; });
    }
    constexpr size_type max_size() const noexcept {
        return sizeof(underlying_type) * 8;
    }

    iterator begin() noexcept { return iterator(*this); }
    const_iterator begin() const noexcept { return const_iterator(*this); }
    const_iterator cbegin() const noexcept { return const_iterator(*this); }

    iterator end() noexcept { return iterator(); }
    const_iterator end() const noexcept { return const_iterator(); }
    const_iterator cend() const noexcept { return const_iterator(); }

    iterator find(enum_type e) { return {*this, e}; }
    const_iterator find(enum_type e) const { return {*this, e}; }

private:
    constexpr explicit flags(underlying_type val) noexcept : val_{val} {}

    underlying_type val_;
};


template <class E> flags<E> operator|(flags<E> f1, flags<E> f2) noexcept {
    return f1 |= f2;
}


template <class E> flags<E> operator|(flags<E> f, E e) noexcept {
    return f |= e;
}


template <class E> flags<E> operator|(E e, flags<E> f) noexcept {
    return f |= e;
}


template <class E>
typename std::enable_if<
    std::is_same<E, typename flags<E>::enum_type>::value,
    flags<E>
>::type
operator|(E e1, E e2) noexcept { return flags<E>{e1} |= e2; }


template <class E> flags<E> operator&(flags<E> f1, flags<E> f2) noexcept {
    return f1 &= f2;
}


template <class E> flags<E> operator&(flags<E> f, E e) noexcept {
    return f &= e;
}


template <class E> flags<E> operator&(E e, flags<E> f) noexcept {;
    return f &= e;
}

template <class E>
typename std::enable_if<
    std::is_same<E, typename flags<E>::enum_type>::value,
    flags<E>
>::type
operator&(E e1, E e2) noexcept { return flags<E>{e1} &= e2; }


template <class E> flags<E> operator^(flags<E> f1, flags<E> f2) noexcept {
    return f1 ^= f2;
}


template <class E> flags<E> operator^(flags<E> f, E e) noexcept {
    return f ^= e;
}


template <class E> flags<E> operator^(E e, flags<E> f) noexcept {
    return f ^= e;
}

template <class E>
typename std::enable_if<
    std::is_same<E, typename flags<E>::enum_type>::value,
    flags<E>
>::type
operator^(E e1, E e2) noexcept { return flags<E>{e1} ^= e2; }


template <class E>
bool operator==(const flags<E> &fl1, const flags<E> &fl2) noexcept {
    return fl1.underlying_value() == fl2.underlying_value();
}


template <class E>
bool operator!=(const flags<E> &fl1, const flags<E> &fl2) noexcept {
    return fl1.underlying_value() != fl2.underlying_value();
}


#endif // ENUM_CLASS_FLAGS_HPP
