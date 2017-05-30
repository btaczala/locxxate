
add_executable(btests main.cpp)
target_link_libraries(btests PRIVATE benchmark locxxate_core)
target_include_directories(btests PRIVATE ${CMAKE_SOURCE_DIR}/3rdParty/benchmark/include)

