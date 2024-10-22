cmake_minimum_required(VERSION 3.27)
project(fract_ol C)

set(CMAKE_C_STANDARD 23)

add_executable(fract_ol main.c
        fract_ol.h
        input.c
        render.c)

target_include_directories(fract_ol PUBLIC ${PROJECT_SOURCE_DIR}/libft)

add_library(mlx STATIC IMPORTED)
set_target_properties(mlx PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/libmlx.a)

add_library(libft STATIC IMPORTED)
set_target_properties(libft PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/libft/libft.a)

target_link_libraries(fract_ol mlx libft)

target_link_libraries(fract_ol "-lXext -lX11 -lm -fopenmp")
