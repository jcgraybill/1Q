cmake_minimum_required(VERSION 3.27.7)
project(1Q VERSION 0.1.0 LANGUAGES C CXX)

set(FASTCGI $ENV{FASTCGI})
include_directories( ${FASTCGI} ${FASTCGI}/include )

file(GLOB SOURCES
    *.h
    *.cpp
)
set(CMAKE_CXX_STANDARD 11)
add_executable(1Q ${SOURCES})
target_link_libraries(1Q ${CMAKE_SOURCE_DIR}/lib/libfcgi++.0.dylib)
target_link_libraries(1Q ${CMAKE_SOURCE_DIR}/lib/libfcgi.0.dylib)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)