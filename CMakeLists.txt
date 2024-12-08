cmake_minimum_required(VERSION 3.31)
project(MANIFOLDEngine)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# LIBRARIES (WE ARE DEFAULTING TO VENDORED FOR NOW)
add_subdirectory(vendor/SDL3 EXCLUDE_FROM_ALL)
add_subdirectory(vendor/SDL_shadercross EXCLUDE_FROM_ALL)
add_subdirectory(vendor/rapidjson EXCLUDE_FROM_ALL)
add_subdirectory(vendor/kazmath EXCLUDE_FROM_ALL)
add_subdirectory(vendor/tinygltf EXCLUDE_FROM_ALL)
add_subdirectory(vendor/vfspp EXCLUDE_FROM_ALL)

include_directories(
        ${SDL3_INCLUDE_DIRS}
        ${RAPIDJSON_INCLUDE_DIRS}
        vendor/kazmath
)

# EXEC
file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)
add_executable(engine ${SOURCES})

add_compile_definitions(VFSPP_ENABLE_MULTITHREADING)
target_link_libraries(engine PRIVATE SDL3::SDL3 kazmath tinygltf vfspp)
