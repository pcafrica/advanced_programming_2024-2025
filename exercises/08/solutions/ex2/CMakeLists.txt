cmake_minimum_required(VERSION 3.12)

project(Ex08_2 VERSION 1.0
  DESCRIPTION "Exercise 2 from session 08"
  LANGUAGES CXX)

add_library(graphics STATIC graphics_lib.cpp)
add_library(math STATIC math_lib.cpp)
target_link_libraries(graphics math)

add_executable(ex3 ex3.cpp)
target_link_libraries(ex3 graphics)
