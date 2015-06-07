#include "common.hpp"

#include <iterator>


void check() {
  Enums es = Enum::One;
  auto beg = std::begin(es), end = std::end(es);

  OtherEnums oes{beg, end};
}
