cmake_minimum_required(VERSION 3.5)

# Set Version Number
set(LIBABITS_VERSION_MAJOR 0)
set(LIBABITS_VERSION_MINOR 1)
set(CMAKE_CC_COMPILER /usr/bin/clang)
set(CMAKE_CXX_COMPILER $ENV{CXX})

project(libabits)

# Set CXX flags
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17")

# Library Section
add_library(libabits INTERFACE)
target_include_directories(libabits INTERFACE src/include)

# Unit tests section
add_executable(libabits_tests src/tests/libabits_tests.cpp)
target_include_directories(libabits_tests PUBLIC src/include)
target_link_libraries(libabits_tests libabits)

message("Completed parse of CMakeLists.txt")
message("Compiler chosen= " ${CMAKE_CXX_COMPILER})

