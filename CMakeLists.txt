project(locxxate CXX)
cmake_minimum_required(VERSION 3.8)

set (CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CXXOPTS_BUILD_EXAMPLES OFF)

add_subdirectory(3rdParty/cxxopts)
add_subdirectory(src)
