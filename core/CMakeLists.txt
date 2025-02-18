cmake_minimum_required(VERSION 3.30)
cmake_policy(SET CMP0048 NEW)

project(MECoreSource VERSION 1.0.0 DESCRIPTION "MANIFOLDEngine Core Source")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

# OPTIONS
option(MANIFOLD_VENDORED "Use vendored libraries when compiling" ON)

# DISABLE TROUBLESOME OPTIONS
set(WITH_VM OFF CACHE INTERNAL "" FORCE)

# SUBDIRECTORIES
if(MANIFOLD_VENDORED)
    add_subdirectory(vendor/SDL3 EXCLUDE_FROM_ALL)
    add_subdirectory(vendor/SDL_shadercross EXCLUDE_FROM_ALL)
    add_subdirectory(vendor/spdlog EXCLUDE_FROM_ALL)
    add_subdirectory(vendor/hashlink EXCLUDE_FROM_ALL)
    add_subdirectory(vendor/JoltPhysics/Build EXCLUDE_FROM_ALL)
endif() # add linking for non vendored lol

find_package(Threads REQUIRED)

# HAXE VM
file(GLOB HAXE_EMBED_SOURCES
        vendor/hashlink/src/code.c
        vendor/hashlink/src/module.c
        vendor/hashlink/src/jit.c)
add_library(HLVM SHARED)
target_sources(HLVM PRIVATE ${HAXE_EMBED_SOURCES})
target_include_directories(HLVM
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/vendor/hashlink/src
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/vendor/hashlink/src>)

# ENGINE LIBRARY
file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)
add_library(MANIFOLDEngine SHARED)
target_sources(MANIFOLDEngine PRIVATE ${SOURCES})
target_include_directories(MANIFOLDEngine
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/src
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
           $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR})

target_link_libraries(MANIFOLDEngine PRIVATE SDL3::SDL3 SDL3_shadercross-shared Threads::Threads Jolt vfspp libhl HLVM spdlog::spdlog stduuid)

add_library(ME::Core ALIAS MANIFOLDEngine)
