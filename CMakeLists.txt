cmake_minimum_required(VERSION 3.14)
project(cxxweb VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenSSL REQUIRED)


set(SOURCE_FILES
    src/app.cpp
    src/net/httpsserver.cpp
    src/net/sslcontext.cpp
    src/net/sslconnection.cpp
    src/net/sslconnectionfactory.cpp
    src/data/bytearray.cpp
    src/data/parserhttprequest.cpp
    src/file/staticfilereader.cpp
    src/template/htmltemplatekey.cpp
    src/request/httprequest.cpp
    src/respone/httprespone.cpp
    src/file/fileengine.cpp
    src/router/router.cpp
    src/file/fileconntenttyperegister.cpp
    src/respone/httpresponerender.cpp
)


add_library(cxxweb ${SOURCE_FILES})

target_include_directories(cxxweb
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)


target_link_libraries(cxxweb PRIVATE OpenSSL::SSL OpenSSL::Crypto)


add_library(cxxweb::cxxweb ALIAS cxxweb)


include(GNUInstallDirs)

install(
    TARGETS cxxweb
    EXPORT cxxwebTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(
    DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    EXPORT cxxwebTargets
    FILE cxxwebTargets.cmake
    NAMESPACE cxxweb::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cxxweb
)


include(CMakePackageConfigHelpers)
configure_package_config_file(
    cmake/cxxwebConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/cxxwebConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cxxweb
)

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/cxxwebConfig.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cxxweb
)
