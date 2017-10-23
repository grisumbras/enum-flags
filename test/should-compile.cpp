#include "common.hpp"


// type traits
static_assert(std::is_pod<Enums>::value,
              "Enums is not POD!");
static_assert(std::is_literal_type<Enums>::value,
              "Enums is not a literal type!");


// associated types

// general
static_assert(std::is_same<Enums::enum_type, Enum>::value,
              "Enums::enum_type is not Enum!");
static_assert(std::is_same<std::underlying_type<Enum>::type,
                           Enums::underlying_type>::value,
              "Enums::underlying_type is different from "
              "underlying type of Enum!");
static_assert(std::is_same<std::make_unsigned<Enums::underlying_type>::type,
                           Enums::impl_type>::value,
              "Enums::impl_type is not unsigned version of "
              "Enums::underlying_type!");

// iterator
using Iterator = Enums::iterator;

static_assert(std::is_literal_type<Iterator>::value,
              "Enums::iterator is not a literal type!");
static_assert(std::is_same<Enums::const_iterator, Iterator>::value,
              "Enums::const_iterator and Enums::iterator are different types!");
static_assert(std::is_same<Iterator::flags_type, Enums>::value,
              "Enums::iterator::flags_type is not Enums!");
static_assert(std::is_same<Iterator::iterator_category,
                           std::forward_iterator_tag>::value,
              "Enums::iterator category is not forward iterator!");
static_assert(std::is_same<Iterator::value_type, Enum>::value,
              "Enums::iterator::value_type is not Enum!");
static_assert(std::is_same<Iterator::reference, const Enum>::value,
              "Enums::iterator::reference is not const Enum!");
// (const) forward iterator requirements
static_assert(std::is_copy_constructible<Iterator>::value
              && std::is_copy_assignable<Iterator>::value
              && std::is_destructible<Iterator>::value
//               && std::is_same<decltype(*std::declval<Iterator &>()),
//                               Iterator::reference>::value
              && std::is_same<decltype(++std::declval<Iterator &>()),
                              Iterator &>::value,
              "Enums::iterator does not model Iterator!");
static_assert(std::is_convertible<
                decltype(std::declval<Iterator>() == std::declval<Iterator>()),
                bool>::value,
              "Enums::iterator does not model EqualityComparable!");
static_assert(std::is_convertible<
                decltype(std::declval<Iterator>() != std::declval<Iterator>()),
                bool>::value
              && std::is_convertible<decltype(*std::declval<Iterator &>()),
                                     Iterator::value_type>::value
              && std::is_convertible<decltype(*std::declval<Iterator &>()++),
                                     Iterator::value_type>::value,
              "Enums::iterator does not model InputIterator!");
static_assert(std::is_default_constructible<Iterator>::value
              && std::is_convertible<decltype(++std::declval<Iterator &>()),
                                     Iterator>::value
              && std::is_convertible<decltype(std::declval<Iterator &>()++),
                                     Iterator>::value,
              "Enums::iterator does not model ForwardIterator!");

// container
static_assert(std::is_same<Enums::iterator::value_type,
                           Enums::value_type>::value,
              "Enums::value_type is not Enums::iterator::value_type!");

static_assert(std::is_same<Enums::iterator::reference, Enums::reference>::value,
              "Enums::reference is not Enums::iterator::reference!");
static_assert(std::is_same<Enums::const_reference, Enums::reference>::value,
              "Enums::const_reference is not Enums::reference!");

static_assert(std::is_same<Enums::iterator::pointer, Enums::pointer>::value,
              "Enums::pointer is not Enums::iterator::pointer!");
static_assert(std::is_same<Enums::enum_type *, Enums::pointer>::value,
              "Enums::pointer is not Enum *!");
static_assert(std::is_same<const Enums::enum_type *,
                           Enums::const_pointer>::value,
              "Enums::const_pointer is not const Enum *!");

static_assert(std::is_arithmetic<Enums::size_type>::value,
              "Enums::size_type is not arithmetic!");

static_assert(std::is_same<Enums::iterator::difference_type,
                           Enums::difference_type>::value,
              "Enums::difference_type is not Enums::iterator::difference_type!"
             );
static_assert(std::is_signed<Enums::difference_type>::value,
              "Enums::difference_type is not signed!");


// constexpr construction
constexpr Enums ec1(flags::empty);
constexpr Enums ec2{flags::empty};
constexpr Enums vc1(Enum::One);
constexpr auto vc2 = Enums(Enum::One);


// constexpr logical operators
constexpr bool l1 = static_cast<bool>(ec1);
constexpr bool l2 = !ec1;
constexpr bool l3 = ec1 == ec2;
constexpr bool l4 = ec1 != ec2;


// constexpr bitwise operators
constexpr auto b1 = ~ec1;

constexpr auto b2 = ec1 | ec2;
constexpr auto b3 = ec1 | Enum::One;
constexpr auto b4 = Enum::One | ec1;
constexpr auto b5 = Enum::One | Enum::Two;

constexpr auto b6 = ec1 & ec2;
constexpr auto b7 = ec1 & Enum::One;
constexpr auto b8 = Enum::One & ec1;
constexpr auto b9 = Enum::One & Enum::Two;

constexpr auto b10 = ec1 ^ ec2;
constexpr auto b11 = ec1 & Enum::One;
constexpr auto b12 = Enum::One ^ ec1;
constexpr auto b13 = Enum::One ^ Enum::Two;


// constexpr conversions
constexpr auto cv1 = ec1.underlying_value();
static_assert(std::is_same<decltype(ec1.underlying_value()),
                           Enums::underlying_type>::value,
              "Enums::underlying_value() did not return an object of type "
              "Enums::underlying_type!");
constexpr auto cv2 = ec1.to_bitset();
constexpr auto cv3 = static_cast<std::bitset<Enums::bit_size()>>(ec1);
static_assert(std::is_same<decltype(cv2), decltype(cv3)>::value,
              "Bitset conversion functions return different types!");


// constexpr container functions
constexpr bool cf1 = ec1.empty();
constexpr Enums::size_type cf2 = ec1.max_size();
constexpr Enums::iterator cf3 = ec1.find(Enum::One);
constexpr Enums::size_type cf4 = ec1.count(Enum::One);


// non-int underlying type with bitwise operators
constexpr SmallEnums s1(SmallEnum::SmallOne);
constexpr auto s2 = s1 | s1;
constexpr auto s3 = s1 & s1;
constexpr auto s4 = s1 ^ s1;


template <class... Ts> void ignore_variables(Ts&&...) {}

void do_ignore_variables() {
  ignore_variables(
    vc1, vc2, l1, l2, l3, l4, b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11,
    b12, b13, cv1, cf1, cf2, cf3, cf4, s2, s3, s4
  );
}
