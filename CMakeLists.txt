cmake_minimum_required(VERSION 3.30)
cmake_policy(SET CMP0048 NEW)

project(MANIFOLDEngine VERSION 1.0.0 DESCRIPTION "MANIFOLDEngine")

add_subdirectory(core)
add_subdirectory(hlext)

function(ME_configure target)
    target_link_libraries(${target} PRIVATE ME::Core ME::HLExt)
    add_custom_command(TARGET ${target} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:me.hdll> "${CMAKE_CURRENT_BINARY_DIR}")
endfunction()
