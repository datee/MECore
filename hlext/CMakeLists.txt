cmake_minimum_required(VERSION 3.30)
cmake_policy(SET CMP0048 NEW)

project(MEHLExt VERSION 1.0.0 DESCRIPTION "ME HashLink Extension")

file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)

add_library(me.hdll SHARED)
target_sources(me.hdll PRIVATE ${SOURCES})
target_link_libraries(me.hdll ME::Core libhl HLVM spdlog::spdlog)

set_target_properties(me.hdll PROPERTIES PREFIX "" OUTPUT_NAME MECore SUFFIX .hdll)

add_library(ME::HLExt ALIAS me.hdll)

# install(TARGETS me.hdll DESTINATION ${HDLL_DESTINATION})
