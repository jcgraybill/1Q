cmake_minimum_required(VERSION 3.27.7)
project(1Q VERSION 0.1.0 LANGUAGES C CXX)

include_directories( /usr/local/include )

file(GLOB SOURCES
    *.h
    *.cpp
)
set(CMAKE_CXX_STANDARD 11)
add_executable(1Q ${SOURCES})
target_link_directories( 1Q PUBLIC /usr/local/lib )
target_link_libraries(1Q libfcgi++.a)
target_link_libraries(1Q libfcgi.a)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)