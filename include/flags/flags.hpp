#ifndef ENUM_CLASS_FLAGS_HPP
#define ENUM_CLASS_FLAGS_HPP


#include <initializer_list>
#include <iterator>
#include <numeric>
#include <type_traits>
#include <utility>


namespace flags {


template <typename E, class Enabler = void> struct is_flags
: public std::false_type {};


template <class E> struct flags;


template <class E>
class FlagsIterator {
public:
  using flags_type = flags<E>;
  using difference_type = std::ptrdiff_t;
  using value_type = E;
  using pointer = value_type *;
  using reference = const value_type;
  using iterator_category = std::forward_iterator_tag;


  constexpr FlagsIterator() noexcept : uvalue_(0), mask_(0) {}

  constexpr FlagsIterator(const FlagsIterator &other) noexcept
  : uvalue_(other.uvalue_), mask_(other.mask_) {}


  FlagsIterator &operator++() noexcept {
    nextMask();
    return *this;
  }
  FlagsIterator operator++(int) noexcept {
    auto copy = *this;
    ++(*this);
    return copy;
  }


  constexpr reference operator*() noexcept {
    return static_cast<value_type>(mask_);
  }


  friend inline constexpr bool operator==(const FlagsIterator &i,
                                          const FlagsIterator &j) noexcept {
    return i.mask_ == j.mask_;
  }

  friend inline constexpr bool operator!=(const FlagsIterator &i,
                                          const FlagsIterator &j) noexcept {
    return i.mask_ != j.mask_;
  }


private:
  template <class E_> friend class flags;

  using impl_type = typename flags_type::impl_type;


  explicit FlagsIterator(impl_type uv) noexcept : mask_(1), uvalue_(uv) {
    if (!(mask_ & uvalue_)) { nextMask(); }
  }

  constexpr FlagsIterator(impl_type uv, E e) noexcept
  : uvalue_(uv)
  , mask_(static_cast<impl_type>(static_cast<impl_type>(e) & uv))
  {}


  void nextMask() noexcept {
    do { mask_ <<= 1; } while (mask_ && !(mask_ & uvalue_));
  }


  impl_type uvalue_;
  impl_type mask_;
};


template <class E> struct flags {
public:
  static_assert(is_flags<E>::value,
                "flags::flags is disallowed for this type; "
                "use ALLOW_FLAGS_FOR_ENUM macro.");

  using enum_type = typename std::decay<E>::type;
  using underlying_type = typename std::underlying_type<enum_type>::type;
  using impl_type = typename std::make_unsigned<underlying_type>::type;

  using iterator = FlagsIterator<enum_type>;
  using const_iterator = iterator;
  using value_type = typename iterator::value_type;
  using reference = typename iterator::reference;
  using const_reference = typename iterator::reference;
  using pointer = enum_type *;
  using const_pointer = const enum_type *;
  using size_type = std::size_t;
  using difference_type = typename iterator::difference_type;

  constexpr flags() noexcept : val_(0) {}

  flags(const flags &fl) = default;
  flags &operator=(const flags &fl) = default;

  flags(flags &&fl) = default;
  flags &operator=(flags &&fl) = default;


  constexpr static std::size_t bit_size = sizeof(impl_type) * 8;


#ifdef ENUM_CLASS_FLAGS_FORBID_IMPLICT_CONVERSION
  explicit
#endif
  constexpr flags(enum_type e) noexcept
  : val_{static_cast<impl_type>(e)} {}

  flags &operator=(enum_type e) noexcept {
    val_ = static_cast<impl_type>(e);
    return *this;
  }


private:
  template <typename T, typename Res = std::nullptr_t>
  using convertible = std::enable_if<
    std::is_convertible<T, enum_type>::value,
    Res>;


public:
  flags(std::initializer_list<enum_type> il) noexcept : val_{0} { insert(il); }

  flags &operator=(std::initializer_list<enum_type> il) noexcept {
    clear();
    insert(il);
  }

  template <class... Args>
  flags(enum_type e, Args... args) noexcept : flags{e, args...} {}


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
    val_ &= static_cast<impl_type>(e);
    return *this;
  }
  flags &operator|=(enum_type e) noexcept {
    val_ |= static_cast<impl_type>(e);
    return *this;
  }
  flags &operator^=(enum_type e) noexcept {
    val_ ^= static_cast<impl_type>(e);
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
    return sizeof(impl_type) * 8;
  }

  iterator begin() const noexcept { return cbegin(); }
  iterator cbegin() const noexcept { return iterator{val_}; }

  iterator end() const noexcept { return {}; }
  iterator cend() const noexcept { return {}; }

  iterator find(enum_type e) const noexcept { return {val_, e}; }

  size_type count(enum_type e) const noexcept {
    return find(e) != end() ? 1 : 0;
  }

  std::pair<iterator, iterator> equal_range(enum_type e) noexcept {
    const auto &self = *this;
    return self.equal_range(e);
  }
  std::pair<const_iterator, const_iterator>
  equal_range(enum_type e) const noexcept {
    auto i = find(e);
    auto j = i;
    return {i, ++j};
  }

  template <class... Args>
  std::pair<iterator, bool> emplace(Args&&... args) noexcept {
    return insert(enum_type{args...});
  }
  template <class... Args>
  iterator emplace_hint (const_iterator, Args&&... args) noexcept {
    return insert(enum_type{args...}).first;
  }

  std::pair<iterator, bool> insert(enum_type e) noexcept {
    auto i = find(e);
    if (i == end()) {
      i.uvalue_ = val_ |= i.mask_ = static_cast<impl_type>(e);
      return {i, true};
    }
    return {i, false};
  }
  std::pair<iterator, bool> insert(const_iterator, enum_type e) noexcept {
    return insert(e);
  }
  template <class InputIter>
  void insert(InputIter i1, InputIter i2) noexcept {
    val_ |= std::accumulate(i1, i2, static_cast<impl_type>(0),
                            [](impl_type i, enum_type e)
                            { return i | static_cast<impl_type>(e); }
                           );
  }
  void insert(const std::initializer_list<enum_type> &il) noexcept {
      insert(il.begin(), il.end());
  }

  iterator erase(const_iterator i) noexcept {
    i.uvalue_ = val_ &= ~i.mask_;
    return ++i;
  }
  size_type erase(enum_type e) noexcept {
    auto e_count = count(e);
    val_ &= ~static_cast<impl_type>(e);
    return e_count;
  }
  iterator erase(const_iterator i1, const_iterator i2) noexcept {
    iterator i;
    i.uvalue_
      = val_
      &= ~std::accumulate(i1, i2, static_cast<impl_type>(0),
                          [](impl_type i, enum_type e)
                          { return i | static_cast<impl_type>(e); }
                         );
    i.mask_ = i2.mask_;
      return ++i;
    }
    void clear() noexcept { val_ = 0; }

private:
  constexpr explicit flags(impl_type val) noexcept : val_{val} {}

  void update_uvalue(iterator &it) const noexcept { it.uvalue_ = val_; }

  impl_type val_;
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


template <class E> flags<E> operator&(flags<E> f1, flags<E> f2) noexcept {
    return f1 &= f2;
}


template <class E> flags<E> operator&(flags<E> f, E e) noexcept {
    return f &= e;
}


template <class E> flags<E> operator&(E e, flags<E> f) noexcept {;
    return f &= e;
}


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
bool operator==(const flags<E> &fl1, const flags<E> &fl2) noexcept {
  return fl1.underlying_value() == fl2.underlying_value();
}


template <class E>
bool operator!=(const flags<E> &fl1, const flags<E> &fl2) noexcept {
  return fl1.underlying_value() != fl2.underlying_value();
}


} // namespace flags


template <class E>
auto operator|(E e1, E e2) noexcept
-> typename std::enable_if<flags::is_flags<E>::value,
                           flags::flags<E>>::type {
  return flags::flags<E>{e1} |= e2;
}


template <class E>
auto operator&(E e1, E e2) noexcept
-> typename std::enable_if<flags::is_flags<E>::value,
                           flags::flags<E>>::type {
  return flags::flags<E>{e1} &= e2;
}


template <class E>
auto operator^(E e1, E e2) noexcept
-> typename std::enable_if<flags::is_flags<E>::value,
                           flags::flags<E>>::type {
  return flags::flags<E>{e1} ^= e2;
}


#define ALLOW_FLAGS_FOR_ENUM(name) \
namespace flags { \
template <> struct is_flags< name > : std::true_type {}; \
}


#endif // ENUM_CLASS_FLAGS_HPP
