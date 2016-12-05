cmake_minimum_required (VERSION 2.6)
project (hash_actor)

if (UNIX)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
endif()

set (CAF_INCLUDE_DIR /usr/local/include)
set (CAF_LIBRARY_DIR /usr/local/lib)

set(SOURCES sha1.hpp sha1.cpp)

#dizinleri binary source tree'ye dahil et.
include_directories(${CAF_INCLUDE_DIR})

#kütüphane dosyaları
link_directories(${CAF_LIBRARY_DIR})

add_executable(app main.cpp ${SOURCES})

target_link_libraries(app caf_core caf_io)