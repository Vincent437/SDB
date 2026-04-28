cmake_minimum_required(VERSION 3.15)

project(sdb LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

add_library(sdb_core
    src/config.cpp
    src/trace.cpp
    src/debugger.cpp
)

target_include_directories(sdb_core
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

add_executable(${PROJECT_NAME} src/main.cpp)

# target_include_directories(${PROJECT_NAME}
#     PRIVATE
#         ${PROJECT_SOURCE_DIR}/include
# )

target_compile_options(${PROJECT_NAME}
    PRIVATE
        -Wall -Wextra -Wpedantic
        $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
        $<$<CONFIG:Debug>:-fno-inline>
)

target_link_libraries(${PROJECT_NAME} PRIVATE sdb_core)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

set(TEST_SOURCES
    tests/test_main.cpp
    tests/test_error.cpp
    tests/test_logger.cpp
    tests/test_config.cpp
    tests/test_launch.cpp
    tests/test_handshake.cpp
    tests/test_debugger.cpp
)

add_executable(my_tests ${TEST_SOURCES})

# target_include_directories(my_tests
#     PRIVATE
#         ${PROJECT_SOURCE_DIR}/include
# )

target_link_libraries(my_tests
    PRIVATE
        GTest::gtest_main
        sdb_core
)

include(GoogleTest)
gtest_discover_tests(my_tests)