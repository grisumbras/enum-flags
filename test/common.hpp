#ifndef ENUM_CLASS_TEST_COMMON_HPP
#define ENUM_CLASS_TEST_COMMON_HPP


#include <flags/flags.hpp>


enum class Enum : int {One = 1, Two = 2, Four = 4, Eight = 8};
ALLOW_FLAGS_FOR_ENUM(Enum)

using Enums = flags::flags<Enum>;


#endif // ENUM_CLASS_TEST_COMMON_HPP
