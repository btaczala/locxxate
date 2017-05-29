add_library(locxxate_core locxxate.cpp)

add_executable(locxxate main.cpp)
target_link_libraries(locxxate locxxate_core stdc++fs)
