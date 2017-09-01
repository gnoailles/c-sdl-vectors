cmake_minimum_required(VERSION 3.8)
project(vector_sdl)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules/")
set(CMAKE_CXX_STANDARD 11)

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2GFX REQUIRED SDL2_gfx)
include_directories(${SDL2_INCLUDE_DIRS})

set(SOURCE_FILES
        const.h
        graphics.c
        graphics.h
        main.c
        Vector.c
        Vector.h
        Particle.c
        Particle.h
        perlin.c
        perlin.h)

add_executable(vector_sdl ${SOURCE_FILES})
target_link_libraries(vector_sdl ${SDL2_LIBRARIES} ${SDL2GFX_LIBRARIES} m)