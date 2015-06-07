#include "common.hpp"

#include <vector>

#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_CASE(set_underlying_value) {
  Enums result;
  constexpr int random_number = 87;
  result.set_underlying_value(random_number);
  BOOST_CHECK(random_number == result.underlying_value());
}


BOOST_AUTO_TEST_CASE(empty_constructor) {
  Enums null{flags::empty};
  BOOST_CHECK(0 == null.underlying_value());
}


BOOST_AUTO_TEST_CASE(enum_constructor_and_assignment) {
  BOOST_CHECK(1 == static_cast<int>(Enum::One));
  Enums one = Enum::One;
  BOOST_CHECK(1 == one.underlying_value());
  one = Enum::One;
  BOOST_CHECK(1 == one.underlying_value());

  BOOST_CHECK(2 == static_cast<int>(Enum::Two));
  Enums two = Enum::Two;
  BOOST_CHECK(2 == two.underlying_value());
  two = Enum::Two;
  BOOST_CHECK(2 == two.underlying_value());
}


BOOST_AUTO_TEST_CASE(equality) {
  const Enums one = Enum::One;
  const Enums two = Enum::Two;

  BOOST_CHECK(one == one);
  BOOST_CHECK(two == two);

  BOOST_CHECK(two != one);
  BOOST_CHECK(one != two);
}


BOOST_AUTO_TEST_CASE(copy_move_swap) {
  const Enums one = Enum::One;

  Enums copy_constructed = one;
  BOOST_CHECK(one == copy_constructed);

  Enums copy_assigned = Enum::Two;
  BOOST_CHECK(one != copy_assigned);
  copy_assigned = one;
  BOOST_CHECK(one == copy_assigned);

  Enums move_constructed = std::move(copy_constructed);
  BOOST_CHECK(one == move_constructed);

  Enums move_assigned = Enum::Two;
  BOOST_CHECK(one != move_assigned);
  move_assigned = std::move(move_constructed);
  BOOST_CHECK(one == move_assigned);

  Enums left = Enum::One, right = Enum::Two;
  swap(left, right);
  BOOST_CHECK((2 == left.underlying_value())
              && (1 == right.underlying_value()));
  left.swap(right);
  BOOST_CHECK((1 == left.underlying_value())
              && (2 == right.underlying_value()));
}


BOOST_AUTO_TEST_CASE(initializer_list_and_variadic_constructor) {
  Enums il_constructed{Enum::One, Enum::Four, Enum::Eight};
  BOOST_CHECK((1 | 4 | 8) == il_constructed.underlying_value());

  Enums il_assigned;
  il_assigned = {Enum::Two, Enum::Four, Enum::Eight};
  BOOST_CHECK((2 | 4 | 8) == il_assigned.underlying_value());

  Enums var_constructed(Enum::One, Enum::Two, Enum::Eight);
  BOOST_CHECK((1 | 2 | 8) == var_constructed.underlying_value());
}


BOOST_AUTO_TEST_CASE(iterator_constructor) {
  std::vector<Enum> vec = {Enum::Two, Enum::Four, Enum::Eight};
  Enums iter_constructed{std::begin(vec), std::end(vec)};
  BOOST_CHECK((2 | 4 | 8) == iter_constructed.underlying_value());
}


BOOST_AUTO_TEST_CASE(bool_conversion_and_negation) {
  const Enums one = Enum::One;
  BOOST_CHECK(one);

  const Enums zero{flags::empty};
  BOOST_CHECK(!zero);

  auto not_one = ~one;
  BOOST_CHECK(~1 == not_one.underlying_value());
}


BOOST_AUTO_TEST_CASE(bit_and) {
  const Enum zero = static_cast<Enum>(0),
             one  = static_cast<Enum>(1);
  const Enums fzero = zero,
              fone  = one;

  Enums result = zero & zero;
  BOOST_CHECK(0 == result.underlying_value());
  result = zero & one;
  BOOST_CHECK(0 == result.underlying_value());
  result = one & zero;
  BOOST_CHECK(0 == result.underlying_value());
  result = one & one;
  BOOST_CHECK(1 == result.underlying_value());

  result = zero & fzero;
  BOOST_CHECK(0 == result.underlying_value());
  result = zero & fone;
  BOOST_CHECK(0 == result.underlying_value());
  result = one & fzero;
  BOOST_CHECK(0 == result.underlying_value());
  result = one & fone;
  BOOST_CHECK(1 == result.underlying_value());

  result = fzero & zero;
  BOOST_CHECK(0 == result.underlying_value());
  result = fzero & one;
  BOOST_CHECK(0 == result.underlying_value());
  result = fone & zero;
  BOOST_CHECK(0 == result.underlying_value());
  result = fone & one;
  BOOST_CHECK(1 == result.underlying_value());

  result = fzero & fzero;
  BOOST_CHECK(0 == result.underlying_value());
  result = fzero & fone;
  BOOST_CHECK(0 == result.underlying_value());
  result = fone & fzero;
  BOOST_CHECK(0 == result.underlying_value());
  result = fone & fone;
  BOOST_CHECK(1 == result.underlying_value());

  result = zero;
  result &= zero;
  BOOST_CHECK(0 == result.underlying_value());
  result = zero;
  result &= one;
  BOOST_CHECK(0 == result.underlying_value());
  result = one;
  result &= zero;
  BOOST_CHECK(0 == result.underlying_value());
  result = one;
  result &= one;
  BOOST_CHECK(1 == result.underlying_value());

  result = zero;
  result &= fzero;
  BOOST_CHECK(0 == result.underlying_value());
  result = zero;
  result &= fone;
  BOOST_CHECK(0 == result.underlying_value());
  result = one;
  result &= fzero;
  BOOST_CHECK(0 == result.underlying_value());
  result = one;
  result &= fone;
  BOOST_CHECK(1 == result.underlying_value());
}


BOOST_AUTO_TEST_CASE(bit_or) {
  const Enum zero = static_cast<Enum>(0);
  const Enum one  = static_cast<Enum>(1);
  const Enums fzero = zero,
              fone  = one;

  Enums result = zero | zero;
  BOOST_CHECK(0 == result.underlying_value());
  result = zero | one;
  BOOST_CHECK(1 == result.underlying_value());
  result = one | zero;
  BOOST_CHECK(1 == result.underlying_value());
  result = one | one;
  BOOST_CHECK(1 == result.underlying_value());

  result = zero | fzero;
  BOOST_CHECK(0 == result.underlying_value());
  result = zero | fone;
  BOOST_CHECK(1 == result.underlying_value());
  result = one | fzero;
  BOOST_CHECK(1 == result.underlying_value());
  result = one | fone;
  BOOST_CHECK(1 == result.underlying_value());

  result = fzero | zero;
  BOOST_CHECK(0 == result.underlying_value());
  result = fzero | one;
  BOOST_CHECK(1 == result.underlying_value());
  result = fone | zero;
  BOOST_CHECK(1 == result.underlying_value());
  result = fone | one;
  BOOST_CHECK(1 == result.underlying_value());

  result = fzero | fzero;
  BOOST_CHECK(0 == result.underlying_value());
  result = fzero | fone;
  BOOST_CHECK(1 == result.underlying_value());
  result = fone | fzero;
  BOOST_CHECK(1 == result.underlying_value());
  result = fone | fone;
  BOOST_CHECK(1 == result.underlying_value());

  result = zero;
  result |= zero;
  BOOST_CHECK(0 == result.underlying_value());
  result = zero;
  result |= one;
  BOOST_CHECK(1 == result.underlying_value());
  result = one;
  result |= zero;
  BOOST_CHECK(1 == result.underlying_value());
  result = one;
  result |= one;
  BOOST_CHECK(1 == result.underlying_value());

  result = zero;
  result |= fzero;
  BOOST_CHECK(0 == result.underlying_value());
  result = zero;
  result |= fone;
  BOOST_CHECK(1 == result.underlying_value());
  result = one;
  result |= fzero;
  BOOST_CHECK(1 == result.underlying_value());
  result = one;
  result |= fone;
  BOOST_CHECK(1 == result.underlying_value());
}


BOOST_AUTO_TEST_CASE(bit_xor) {
  const Enum zero = static_cast<Enum>(0);
  const Enum one  = static_cast<Enum>(1);
  const Enums fzero = zero,
              fone  = one;

  Enums result = zero ^ zero;
  BOOST_CHECK(0 == result.underlying_value());
  result = zero ^ one;
  BOOST_CHECK(1 == result.underlying_value());
  result = one ^ zero;
  BOOST_CHECK(1 == result.underlying_value());
  result = one ^ one;
  BOOST_CHECK(0 == result.underlying_value());

  result = zero ^ fzero;
  BOOST_CHECK(0 == result.underlying_value());
  result = zero ^ fone;
  BOOST_CHECK(1 == result.underlying_value());
  result = one ^ fzero;
  BOOST_CHECK(1 == result.underlying_value());
  result = one ^ fone;
  BOOST_CHECK(0 == result.underlying_value());

  result = fzero ^ zero;
  BOOST_CHECK(0 == result.underlying_value());
  result = fzero ^ one;
  BOOST_CHECK(1 == result.underlying_value());
  result = fone ^ zero;
  BOOST_CHECK(1 == result.underlying_value());
  result = fone ^ one;
  BOOST_CHECK(0 == result.underlying_value());

  result = fzero ^ fzero;
  BOOST_CHECK(0 == result.underlying_value());
  result = fzero ^ fone;
  BOOST_CHECK(1 == result.underlying_value());
  result = fone ^ fzero;
  BOOST_CHECK(1 == result.underlying_value());
  result = fone ^ fone;
  BOOST_CHECK(0 == result.underlying_value());

  result = zero;
  result ^= zero;
  BOOST_CHECK(0 == result.underlying_value());
  result = zero;
  result ^= one;
  BOOST_CHECK(1 == result.underlying_value());
  result = one;
  result ^= zero;
  BOOST_CHECK(1 == result.underlying_value());
  result = one;
  result ^= one;
  BOOST_CHECK(0 == result.underlying_value());

  result = zero;
  result ^= fzero;
  BOOST_CHECK(0 == result.underlying_value());
  result = zero;
  result ^= fone;
  BOOST_CHECK(1 == result.underlying_value());
  result = one;
  result ^= fzero;
  BOOST_CHECK(1 == result.underlying_value());
  result = one;
  result ^= fone;
  BOOST_CHECK(0 == result.underlying_value());
}


BOOST_AUTO_TEST_CASE(bitset) {
  auto a_bitset = (Enum::Two | Enum::Four | Enum::Eight).to_bitset();
  BOOST_CHECK((2 | 4 | 8) == a_bitset.to_ulong());

  a_bitset = (decltype(a_bitset))(Enum::One | Enum::Four | Enum::Eight);
  BOOST_CHECK((1 | 4 | 8) == a_bitset.to_ulong());
}
