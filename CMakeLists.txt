cmake_minimum_required(VERSION 3.30)
cmake_policy(SET CMP0048 NEW)

project(MANIFOLDEngine VERSION 1.0.0 DESCRIPTION "MANIFOLDEngine Core")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# OPTIONS
option(MANIFOLD_VENDORED "Use vendored libraries when compiling" ON)

# SUBDIRECTORIES
if(MANIFOLD_VENDORED)
    add_subdirectory(vendor/SDL3 EXCLUDE_FROM_ALL)
    add_subdirectory(vendor/SDL_shadercross EXCLUDE_FROM_ALL)
    add_subdirectory(vendor/rapidjson EXCLUDE_FROM_ALL)
    add_subdirectory(vendor/vfspp EXCLUDE_FROM_ALL)
    add_subdirectory(vendor/mathfu EXCLUDE_FROM_ALL)
    add_subdirectory(vendor/hashlink EXCLUDE_FROM_ALL)
endif() # add linking for non vendored lol

# SOURCES
file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)
set(HAXE_EMBED_SOURCES vendor/hashlink/src/code.c vendor/hashlink/src/module.c vendor/hashlink/src/jit.c)

add_library(MANIFOLDEngine SHARED)
target_sources(MANIFOLDEngine PRIVATE ${SOURCES})

target_include_directories(MANIFOLDEngine
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/src
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
           $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR})
mathfu_configure_flags(MANIFOLDEngine) # this adds includes

target_link_libraries(MANIFOLDEngine PRIVATE SDL3::SDL3 SDL3_shadercross-shared RapidJSON vfspp)

