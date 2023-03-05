cmake_minimum_required(VERSION 3.24)
project(Task_2)

set(CMAKE_CXX_STANDARD 17)

set(TEST_BUILD  OFF)

if (${TEST_BUILD})
    message("test build")
    add_subdirectory(GTest/googletest)
    include_directories(GTest/googletest/googletest/include)

    add_executable(Task_2 main.cpp Tests.cpp main.h)
    target_link_libraries(Task_2 gtest)
else()
    message("production build")
    add_executable(Task_2 main.cpp main.h)
endif()