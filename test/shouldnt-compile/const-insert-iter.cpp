#include "common.hpp"


void check() {
  const Enums es1;
  Enum arr[] = {Enum::One};
  es1.insert(arr, arr + 1);
}
