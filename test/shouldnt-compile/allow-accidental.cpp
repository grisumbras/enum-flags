#include "common.hpp"


enum class AnotherEnum { One = 1, Two = 2 };


void check() {
  auto aes = AnotherEnum::One | AnotherEnum::Two;
}
