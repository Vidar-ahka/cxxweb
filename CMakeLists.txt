cmake_minimum_required(VERSION 3.14)

project(cxxweb)
set(CMAKE_CXX_STANDARD 17)
find_package(OpenSSL REQUIRED)

set(SOURCE_FILES
    
    src/net/httpsserver.cpp
    src/net/sslcontext.cpp
    src/byte/bytearray.cpp
    src/net/sslconnection.cpp
)


add_library(cxxweb ${SOURCE_FILES})

target_include_directories(cxxweb PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include/)
target_include_directories(cxxweb PRIVATE ${OPENSSL_INCLUDE_DIR})
target_link_libraries(cxxweb PRIVATE ${OPENSSL_LIBRARIES})


set(TEST  FALSE)

if( TEST )
    add_subdirectory(${CMAKE_SOURCE_DIR}/test)
endif()

