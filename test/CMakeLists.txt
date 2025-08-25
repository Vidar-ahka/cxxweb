
cmake_minimum_required(VERSION 3.14)
project(test_cxxweb LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

enable_testing()



include(FetchContent)


FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(TEST_FILE 
    test_bytearray.cpp
)

add_executable(
    ${PROJECT_NAME}
    ${TEST_FILE} 
)

target_link_libraries( ${PROJECT_NAME}
    PRIVATE
        cxxweb
        GTest::gtest
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
