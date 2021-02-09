
cmake_minimum_required(VERSION 3.10)

project(MyApp CXX)

set(ZEN_NAMESPACE "myapp::zen" CACHE INTERNAL "The namespace that this project will use" FORCE)
add_subdirectory(subprojects/zen EXCLUDE_FROM_ALL)

add_executable(myapp src/main.cc)
target_link_libraries(myapp PRIVATE zen)

