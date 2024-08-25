cmake_minimum_required(VERSION 3.30)

# Set the project name
project(Karakuri)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(dependencies)

# 
add_library(Karakuri STATIC
    # Public Headers
    include/animation_data.h
    include/animation_player.h
    include/aseprite.h
    include/buttons.h
    include/cell_data.h
    include/circle.h
    include/collision.h
    include/colour.h
    include/frame_data.h
    include/game.h
    include/gamepad.h
    include/graphics_device.h
    include/json.hpp
    include/karakuri.h
    include/keyboard.h
    include/keys.h
    include/math_utility.h
    include/matrix.h
    include/mouse.h
    include/rectangle.h
    include/song.h
    include/sound_effect.h
    include/sprite_mirror.h
    include/texture.h
    include/timer.h
    include/vector2.h
    include/vector3.h
    include/shader.h
    include/glad.h
    include/khrplatform.h
    include/update_component.h
    include/update_manager.h
    include/renderer.h
    # Source Files
    src/animation_data.cpp
    src/animation_player.cpp
    src/aseprite.cpp
    src/cell_data.cpp
    src/circle.cpp
    src/collision.cpp
    src/colour.cpp
    src/frame_data.cpp
    src/game.cpp
    src/gamepad.cpp
    src/glad.c
    src/graphics_device.cpp
    src/keyboard.cpp
    src/mouse.cpp
    src/rectangle.cpp
    src/shader.cpp
    src/song.cpp
    src/sound_effect.cpp
    src/stb_image.cpp
    src/stb_image.h
    src/texture.cpp
    src/timer.cpp
    src/update_manager.cpp
    src/renderer.cpp)

# Link spdlog to Karakuri
target_link_libraries(Karakuri PRIVATE spdlog::spdlog SDL2::SDL2-static SDL2_mixer::SDL2_mixer-static) 

target_include_directories(Karakuri PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)