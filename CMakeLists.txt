project(locxxate CXX)
cmake_minimum_required(VERSION 3.8)

enable_testing()
option(WITH_BENCHMARK "Build with benchmark" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CXXOPTS_BUILD_EXAMPLES OFF)

set(CXX_FLAGS "-Wall")
list(APPEND CMAKE_CXX_FLAGS "")
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CXX_FLAGS "${CXX_FLAGS} -Wno-gnu-statement-expression")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CXX_FLAGS "${CXX_FLAGS} -Wno-misleading-indentation")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_FLAGS}")

add_subdirectory(3rdParty/cxxopts)
set(SPDLOG_BUILD_TESTING OFF)
add_subdirectory(3rdParty/spdlog)
add_subdirectory(src)
add_subdirectory(tests)

if (WITH_BENCHMARK)
    set(BENCHMARK_ENABLE_TESTING OFF)
    add_subdirectory(3rdParty/benchmark)
    add_subdirectory(btests)
endif()
