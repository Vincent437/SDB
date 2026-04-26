cmake_minimum_required(VERSION 3.15)

project(sdb LANGUAGE CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(SOURCES
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        -Wall -Wextra -Wpedantic
)

# target_link_libraries(${PROJECT_NAME} PRIVATE some_library)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(my_tests tests/test_main.cpp)

target_link_libraries(my_tests
    PRIVATE
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(my_tests)uq dao