#include "common.hpp"


void check() {
  Enums e = Enum::One;
  auto i = e.begin();
  *i = Enum::One;
}
