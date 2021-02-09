
cmake_minimum_required(VERSION 3.10)

project(MyApp CXX)

add_subdirectory(subprojects/zen EXCLUDE_FROM_ALL)

add_executable(myapp src/main.cc)
target_link_libraries(myapp zen)

