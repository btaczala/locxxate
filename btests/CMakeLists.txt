
add_executable(btests main.cpp)
target_link_libraries(btests PRIVATE benchmark locxxate_core)
target_compile_definitions(btests PRIVATE "TEST_DIR=\"${CMAKE_SOURCE_DIR}/tests/\"")
target_include_directories(btests PRIVATE ${CMAKE_SOURCE_DIR}/3rdParty/benchmark/include)

