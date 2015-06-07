#ifndef ENUM_CLASS_TEST_SHOULDNT_COMPILE_COMMON_HPP
#define ENUM_CLASS_TEST_SHOULDNT_COMPILE_COMMON_HPP


#include <flags/flags.hpp>


enum class Enum { One = 1 };
ALLOW_FLAGS_FOR_ENUM(Enum)
using Enums = flags::flags<Enum>;


enum class OtherEnum { One = 1 };
ALLOW_FLAGS_FOR_ENUM(OtherEnum)
using OtherEnums = flags::flags<OtherEnum>;


#endif // ENUM_CLASS_TEST_SHOULDNT_COMPILE_COMMON_HPP
