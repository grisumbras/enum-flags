#include <flags/flags.hpp>


enum class SomeEnum { One = 1 };
using SomeEnums = flags::flags<SomeEnum>; // no falgs::is_flags<> specialization
                                          // for SomeEnum

void check() {
  SomeEnums se;
}
