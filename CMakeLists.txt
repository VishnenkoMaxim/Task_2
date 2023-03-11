cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 17)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})
project(Task_2 VERSION ${PROJECT_VERSION})

set(TEST_BUILD ON)

configure_file(version.h.in version.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

if (${TEST_BUILD})
    message("test build")
    add_subdirectory(GTest/googletest)
    include_directories(GTest/googletest/googletest/include)

    add_executable(Task_2 main.cpp Tests.cpp main.h)
    target_link_libraries(Task_2 gtest)
else()
    message("production build")
    add_executable(Task_2 main.cpp)
endif()

set_target_properties(Task_2 PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
target_compile_options(Task_2 PRIVATE -Wall -Wextra -pedantic)

install(TARGETS Task_2 RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Vishnenko Maxim")

include(CPack)