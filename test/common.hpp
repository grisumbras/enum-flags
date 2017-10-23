#ifndef ENUM_CLASS_TEST_COMMON_HPP
#define ENUM_CLASS_TEST_COMMON_HPP


#include <flags/flags.hpp>


enum class Enum : int {One = 1, Two = 2, Four = 4, Eight = 8};
ALLOW_FLAGS_FOR_ENUM(Enum)

using Enums = flags::flags<Enum>;


enum class SmallEnum : unsigned char {SmallOne = 1, SmallTwo = 2, SmallFour = 4, SmallEight = 8};
ALLOW_FLAGS_FOR_ENUM(SmallEnum)

using SmallEnums = flags::flags<SmallEnum>;


#endif // ENUM_CLASS_TEST_COMMON_HPP
