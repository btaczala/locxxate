find_package(Threads REQUIRED)
find_package(Boost REQUIRED)

add_library(locxxate_core locxxate.cpp db.cpp dbsimple_file.cpp)
target_link_libraries(locxxate_core PUBLIC stdc++fs spdlog ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(locxxate_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${Boost_INCLUDE_DIR})

add_executable(locxxate main.cpp)
target_link_libraries(locxxate locxxate_core cxxopts)
