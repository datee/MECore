cmake_minimum_required(VERSION 3.30)
cmake_policy(SET CMP0048 NEW)

project(MECore VERSION 1.0.0 DESCRIPTION "MANIFOLDEngine Core")

add_subdirectory(core)
add_subdirectory(extension)

function(MECore_configure target)
    target_link_libraries(${target} PRIVATE ME::Core ME::CoreExt nvrhi Jolt::Jolt spdlog::spdlog vfspp stduuid imgui)
    add_custom_command(TARGET ${target} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:MECoreExt> "${CMAKE_CURRENT_BINARY_DIR}")
endfunction()
