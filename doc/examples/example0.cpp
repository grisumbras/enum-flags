#include <flags/flags.hpp>

enum class MyEnum { Value1 = 1 , Value2 = 2 };
ALLOW_FLAGS_FOR_ENUM(MyEnum)

int main() {
  auto mask = MyEnum::Value1 | MyEnum::Value2;
  if (mask & MyEnum::Value2) {
    // do something
  }
  return 0;
}
