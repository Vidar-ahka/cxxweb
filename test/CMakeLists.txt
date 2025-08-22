cmake_minimum_required(VERSION 3.14)
project(ByteArrayTests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(test_cxxweb
    sslconnection_test.cpp  # твой тестовый файл
)

target_link_libraries(test_cxxweb PRIVATE
    GTest::gtest_main
    GTest::gmock
    cxxweb
)

include(GoogleTest)
gtest_discover_tests(test_cxxweb)
