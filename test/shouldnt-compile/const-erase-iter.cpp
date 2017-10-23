#include "common.hpp"


void check() {
  const auto es1 = Enums{};
  Enum arr[] = {Enum::One};
  es1.erase(arr);
}
