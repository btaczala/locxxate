
add_executable(tests main.cpp locxxate_tests.cpp dbsimple_tests.cpp)
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/3rdParty/catch/include ${CMAKE_SOURCE_DIR}/src)
target_compile_definitions(tests PRIVATE "TEST_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}\"")
target_link_libraries(tests locxxate_core)
add_test(locxxate_tests tests)
