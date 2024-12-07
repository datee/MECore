cmake_minimum_required(VERSION 3.31)
project(MANIFOLDEngine)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE sources source/*.cpp source/*.h)

add_subdirectory(subprojects/SDL3 EXCLUDE_FROM_ALL)
add_subdirectory(subprojects/kazmath EXCLUDE_FROM_ALL)

# RAPID JSON IS A PAIN
# SO ITS JUST INCLUDED I DONT CARE
include_directories(include/rapidjson)

# tinygltf lol
set(TINYGLTF_HEADER_ONLY OFF CACHE INTERNAL "" FORCE)
set(TINYGLTF_INSTALL OFF CACHE INTERNAL "" FORCE)
add_subdirectory(subprojects/tinygltf)

add_subdirectory(subprojects/vfspp)

add_executable(engine ${sources})
add_compile_definitions(TINYGLTF_USE_RAPIDJSON TINYGLTF_USE_CPP14)
add_compile_definitions(VFSPP_ENABLE_MULTITHREADING)
target_link_libraries(engine PRIVATE SDL3::SDL3 kazmath tinygltf vfspp)
