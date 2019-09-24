#include "common.hpp"

#include <vector>

#include <boost/core/lightweight_test.hpp>


namespace flags {
template <class E>
auto operator<<(std::ostream& o, flags<E> fl) -> std::ostream& {
  return o << "flags<" << fl.underlying_value() << '>';
}
} // namespace flags


void test_set_underlying_value() {
  Enums result;
  constexpr int random_number = 87;
  result.set_underlying_value(random_number);
  BOOST_TEST_EQ(random_number, result.underlying_value());
}


void test_empty_constructor() {
  Enums null{flags::empty};
  BOOST_TEST_EQ(0, null.underlying_value());
}


void test_enum_constructor_and_assignment() {
  BOOST_TEST_EQ(1, static_cast<int>(Enum::One));
  Enums one = Enum::One;
  BOOST_TEST_EQ(1, one.underlying_value());
  one = Enum::One;
  BOOST_TEST_EQ(1, one.underlying_value());

  BOOST_TEST_EQ(2, static_cast<int>(Enum::Two));
  Enums two = Enum::Two;
  BOOST_TEST_EQ(2, two.underlying_value());
  two = Enum::Two;
  BOOST_TEST_EQ(2, two.underlying_value());
}


void test_equality() {
  const Enums one = Enum::One;
  const Enums two = Enum::Two;

  BOOST_TEST_EQ(one, one);
  BOOST_TEST_EQ(two, two);

  BOOST_TEST_NE(two, one);
  BOOST_TEST_NE(one, two);
}


void test_copy_move_swap() {
  const Enums one = Enum::One;

  Enums copy_constructed = one;
  BOOST_TEST_EQ(one, copy_constructed);

  Enums copy_assigned = Enum::Two;
  BOOST_TEST_NE(one, copy_assigned);
  copy_assigned = one;
  BOOST_TEST_EQ(one, copy_assigned);

  Enums move_constructed = std::move(copy_constructed);
  BOOST_TEST_EQ(one, move_constructed);

  Enums move_assigned = Enum::Two;
  BOOST_TEST_NE(one, move_assigned);
  move_assigned = std::move(move_constructed);
  BOOST_TEST_EQ(one, move_assigned);

  Enums left = Enum::One, right = Enum::Two;
  swap(left, right);
  BOOST_TEST_EQ(2, left.underlying_value());
  BOOST_TEST_EQ(1, right.underlying_value());

  left.swap(right);
  BOOST_TEST_EQ(1, left.underlying_value());
  BOOST_TEST_EQ(2, right.underlying_value());
}


void test_initializer_list_and_variadic_constructor() {
  Enums il_constructed{Enum::One, Enum::Four, Enum::Eight};
  BOOST_TEST_EQ((1 | 4 | 8), il_constructed.underlying_value());

  Enums il_assigned;
  il_assigned = {Enum::Two, Enum::Four, Enum::Eight};
  BOOST_TEST_EQ((2 | 4 | 8), il_assigned.underlying_value());

  Enums var_constructed(Enum::One, Enum::Two, Enum::Eight);
  BOOST_TEST_EQ((1 | 2 | 8), var_constructed.underlying_value());
}


void test_iterator_constructor() {
  std::vector<Enum> vec = {Enum::Two, Enum::Four, Enum::Eight};
  Enums iter_constructed{std::begin(vec), std::end(vec)};
  BOOST_TEST_EQ((2 | 4 | 8), iter_constructed.underlying_value());
}


void test_bool_conversion_and_negation() {
  const Enums one = Enum::One;
  BOOST_TEST(one);

  const Enums zero{flags::empty};
  BOOST_TEST_NOT(zero);

  auto not_one = ~one;
  BOOST_TEST_EQ(~1, not_one.underlying_value());
}


void test_bit_and() {
  const Enum zero = static_cast<Enum>(0),
             one  = static_cast<Enum>(1);
  const Enums fzero = zero,
              fone  = one;

  Enums result = zero & zero;
  BOOST_TEST_EQ(0, result.underlying_value());
  result = zero & one;
  BOOST_TEST_EQ(0, result.underlying_value());
  result = one & zero;
  BOOST_TEST_EQ(0, result.underlying_value());
  result = one & one;
  BOOST_TEST_EQ(1, result.underlying_value());

  result = zero & fzero;
  BOOST_TEST_EQ(0, result.underlying_value());
  result = zero & fone;
  BOOST_TEST_EQ(0, result.underlying_value());
  result = one & fzero;
  BOOST_TEST_EQ(0, result.underlying_value());
  result = one & fone;
  BOOST_TEST_EQ(1, result.underlying_value());

  result = fzero & zero;
  BOOST_TEST_EQ(0, result.underlying_value());
  result = fzero & one;
  BOOST_TEST_EQ(0, result.underlying_value());
  result = fone & zero;
  BOOST_TEST_EQ(0, result.underlying_value());
  result = fone & one;
  BOOST_TEST_EQ(1, result.underlying_value());

  result = fzero & fzero;
  BOOST_TEST_EQ(0, result.underlying_value());
  result = fzero & fone;
  BOOST_TEST_EQ(0, result.underlying_value());
  result = fone & fzero;
  BOOST_TEST_EQ(0, result.underlying_value());
  result = fone & fone;
  BOOST_TEST_EQ(1, result.underlying_value());

  result = zero;
  result &= zero;
  BOOST_TEST_EQ(0, result.underlying_value());
  result = zero;
  result &= one;
  BOOST_TEST_EQ(0, result.underlying_value());
  result = one;
  result &= zero;
  BOOST_TEST_EQ(0, result.underlying_value());
  result = one;
  result &= one;
  BOOST_TEST_EQ(1, result.underlying_value());

  result = zero;
  result &= fzero;
  BOOST_TEST_EQ(0, result.underlying_value());
  result = zero;
  result &= fone;
  BOOST_TEST_EQ(0, result.underlying_value());
  result = one;
  result &= fzero;
  BOOST_TEST_EQ(0, result.underlying_value());
  result = one;
  result &= fone;
  BOOST_TEST_EQ(1, result.underlying_value());
}


void test_bit_or() {
  const Enum zero = static_cast<Enum>(0);
  const Enum one  = static_cast<Enum>(1);
  const Enums fzero = zero,
              fone  = one;

  Enums result = zero | zero;
  BOOST_TEST_EQ(0, result.underlying_value());
  result = zero | one;
  BOOST_TEST_EQ(1, result.underlying_value());
  result = one | zero;
  BOOST_TEST_EQ(1, result.underlying_value());
  result = one | one;
  BOOST_TEST_EQ(1, result.underlying_value());

  result = zero | fzero;
  BOOST_TEST_EQ(0, result.underlying_value());
  result = zero | fone;
  BOOST_TEST_EQ(1, result.underlying_value());
  result = one | fzero;
  BOOST_TEST_EQ(1, result.underlying_value());
  result = one | fone;
  BOOST_TEST_EQ(1, result.underlying_value());

  result = fzero | zero;
  BOOST_TEST_EQ(0, result.underlying_value());
  result = fzero | one;
  BOOST_TEST_EQ(1, result.underlying_value());
  result = fone | zero;
  BOOST_TEST_EQ(1, result.underlying_value());
  result = fone | one;
  BOOST_TEST_EQ(1, result.underlying_value());

  result = fzero | fzero;
  BOOST_TEST_EQ(0, result.underlying_value());
  result = fzero | fone;
  BOOST_TEST_EQ(1, result.underlying_value());
  result = fone | fzero;
  BOOST_TEST_EQ(1, result.underlying_value());
  result = fone | fone;
  BOOST_TEST_EQ(1, result.underlying_value());

  result = zero;
  result |= zero;
  BOOST_TEST_EQ(0, result.underlying_value());
  result = zero;
  result |= one;
  BOOST_TEST_EQ(1, result.underlying_value());
  result = one;
  result |= zero;
  BOOST_TEST_EQ(1, result.underlying_value());
  result = one;
  result |= one;
  BOOST_TEST_EQ(1, result.underlying_value());

  result = zero;
  result |= fzero;
  BOOST_TEST_EQ(0, result.underlying_value());
  result = zero;
  result |= fone;
  BOOST_TEST_EQ(1, result.underlying_value());
  result = one;
  result |= fzero;
  BOOST_TEST_EQ(1, result.underlying_value());
  result = one;
  result |= fone;
  BOOST_TEST_EQ(1, result.underlying_value());
}


void test_bit_xor() {
  const Enum zero = static_cast<Enum>(0);
  const Enum one  = static_cast<Enum>(1);
  const Enums fzero = zero,
              fone  = one;

  Enums result = zero ^ zero;
  BOOST_TEST_EQ(0, result.underlying_value());
  result = zero ^ one;
  BOOST_TEST_EQ(1, result.underlying_value());
  result = one ^ zero;
  BOOST_TEST_EQ(1, result.underlying_value());
  result = one ^ one;
  BOOST_TEST_EQ(0, result.underlying_value());

  result = zero ^ fzero;
  BOOST_TEST_EQ(0, result.underlying_value());
  result = zero ^ fone;
  BOOST_TEST_EQ(1, result.underlying_value());
  result = one ^ fzero;
  BOOST_TEST_EQ(1, result.underlying_value());
  result = one ^ fone;
  BOOST_TEST_EQ(0, result.underlying_value());

  result = fzero ^ zero;
  BOOST_TEST_EQ(0, result.underlying_value());
  result = fzero ^ one;
  BOOST_TEST_EQ(1, result.underlying_value());
  result = fone ^ zero;
  BOOST_TEST_EQ(1, result.underlying_value());
  result = fone ^ one;
  BOOST_TEST_EQ(0, result.underlying_value());

  result = fzero ^ fzero;
  BOOST_TEST_EQ(0, result.underlying_value());
  result = fzero ^ fone;
  BOOST_TEST_EQ(1, result.underlying_value());
  result = fone ^ fzero;
  BOOST_TEST_EQ(1, result.underlying_value());
  result = fone ^ fone;
  BOOST_TEST_EQ(0, result.underlying_value());

  result = zero;
  result ^= zero;
  BOOST_TEST_EQ(0, result.underlying_value());
  result = zero;
  result ^= one;
  BOOST_TEST_EQ(1, result.underlying_value());
  result = one;
  result ^= zero;
  BOOST_TEST_EQ(1, result.underlying_value());
  result = one;
  result ^= one;
  BOOST_TEST_EQ(0, result.underlying_value());

  result = zero;
  result ^= fzero;
  BOOST_TEST_EQ(0, result.underlying_value());
  result = zero;
  result ^= fone;
  BOOST_TEST_EQ(1, result.underlying_value());
  result = one;
  result ^= fzero;
  BOOST_TEST_EQ(1, result.underlying_value());
  result = one;
  result ^= fone;
  BOOST_TEST_EQ(0, result.underlying_value());
}


void test_bitset() {
  auto a_bitset = (Enum::Two | Enum::Four | Enum::Eight).to_bitset();
  BOOST_TEST_EQ((2 | 4 | 8), a_bitset.to_ulong());

  a_bitset = (decltype(a_bitset))(Enum::One | Enum::Four | Enum::Eight);
  BOOST_TEST_EQ((1 | 4 | 8), a_bitset.to_ulong());
}

void test_erase() {
  Enums flags(Enum::Two, Enum::Four, Enum::Eight);
  BOOST_TEST_EQ((2 | 4 | 8), flags.underlying_value());

  // erase unsets flag if set:
  flags.erase(Enum::Four);
  BOOST_TEST_EQ((2 | 8), flags.underlying_value());
  // erase is noop if not set:
  flags.erase(Enum::Four);
  BOOST_TEST_EQ((2 | 8), flags.underlying_value());

  // erase unsets flag if set:
  flags.erase(Enum::Two);
  flags.erase(Enum::Eight);
  BOOST_TEST_EQ(0, flags.underlying_value());
  // erase is noop if not set:
  flags.erase(Enum::Two);
  flags.erase(Enum::Eight);
  BOOST_TEST_EQ(0, flags.underlying_value());
}

void test_erase_iterator() {
  Enums flags(Enum::One, Enum::Two, Enum::Four, Enum::Eight);
  BOOST_TEST_EQ((1 | 2 | 4 | 8), flags.underlying_value());

  // erase single value via iterator:
  auto it1 = flags.erase(flags.find(Enum::Four));
  BOOST_TEST_EQ((1 | 2 | 8), flags.underlying_value());
  BOOST_TEST_EQ(8, static_cast<int>(*it1));

  // erase range via iterator:
  auto it2 = flags.erase(flags.begin(), std::next(std::next(flags.begin())));
  BOOST_TEST_EQ(8, flags.underlying_value());
  BOOST_TEST_EQ(8, static_cast<int>(*it2));
}

int main() {
  test_set_underlying_value();
  test_empty_constructor();
  test_enum_constructor_and_assignment();
  test_equality();
  test_copy_move_swap();
  test_initializer_list_and_variadic_constructor();
  test_iterator_constructor();
  test_bool_conversion_and_negation();
  test_bit_and();
  test_bit_or();
  test_bit_xor();
  test_bitset();
  test_erase();
  test_erase_iterator();
  return boost::report_errors();
}
