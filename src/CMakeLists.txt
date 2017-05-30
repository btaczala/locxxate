add_library(locxxate_core locxxate.cpp)
target_link_libraries(locxxate_core PUBLIC stdc++fs)

add_executable(locxxate main.cpp)
target_link_libraries(locxxate locxxate_core cxxopts)
