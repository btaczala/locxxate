find_package(Threads)

add_library(locxxate_core locxxate.cpp db.cpp)
target_link_libraries(locxxate_core PUBLIC stdc++fs spdlog ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(locxxate_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(locxxate main.cpp)
target_link_libraries(locxxate locxxate_core cxxopts)
