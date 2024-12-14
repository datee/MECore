cmake_minimum_required(VERSION 3.31)
project(MANIFOLDEngine)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# LIBRARIES (WE ARE DEFAULTING TO VENDORED FOR NOW)
add_subdirectory(vendor/SDL3 EXCLUDE_FROM_ALL)
add_subdirectory(vendor/SDL_shadercross EXCLUDE_FROM_ALL)
add_subdirectory(vendor/rapidjson EXCLUDE_FROM_ALL)
add_subdirectory(vendor/tinygltf EXCLUDE_FROM_ALL)
add_subdirectory(vendor/vfspp EXCLUDE_FROM_ALL)
add_subdirectory(vendor/mathfu EXCLUDE_FROM_ALL)

# BUILD MATHFU
# add_library(mathfu)
# target_sources(mathfu INTERFACE ${MATHFU_HEADERS})

include_directories(
        ${SDL3_INCLUDE_DIRS}
        ${RAPIDJSON_INCLUDE_DIRS}
        vendor/vfspp/include
        vendor/mathfu/include
        vendor/mathfu/dependencies/vectorial/include
        vendor/imgui
)

# EXEC
add_custom_target(assets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)
file(GLOB IMGUI_SOURCES vendor/imgui/*.h, vendor/imgui/*cpp)
set(IMGUI_BACKENDS vendor/imgui/backends/imgui_impl_sdl3.cpp vendor/imgui/backends/imgui_impl_sdl3.h)

add_executable(engine ${SOURCES} ${IMGUI_SOURCES} ${IMGUI_BACKENDS})
add_dependencies(engine assets)

set(LIBRARIES SDL3::SDL3 SDL3_shadercross-shared RapidJSON tinygltf vfspp)

mathfu_configure_flags(engine)
target_link_libraries(engine PRIVATE ${LIBRARIES})

install(TARGETS engine RUNTIME DESTINATION bin)
include(CPack)
