cmake_minimum_required(VERSION 3.30)
cmake_policy(SET CMP0048 NEW)

project(MECoreExt VERSION 1.0.0 DESCRIPTION "MECore HashLink Extension")

file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)

add_library(MECoreExt SHARED)
target_sources(MECoreExt PRIVATE ${SOURCES})
target_link_libraries(MECoreExt ME::Core SDL3::SDL3 Jolt libhl HLVM spdlog::spdlog stduuid)

set_target_properties(MECoreExt PROPERTIES PREFIX "" OUTPUT_NAME MECore SUFFIX .hdll)

add_library(ME::CoreExt ALIAS MECoreExt)
