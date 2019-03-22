cmake_minimum_required(VERSION 3.0)

project(EnumFlagsUser)

find_package(EnumFlags REQUIRED)

add_executable(app main.cpp)
target_link_libraries(app EnumFlags::EnumFlags)
