cmake_minimum_required(VERSION 3.27)
project(fract_ol C)

set(CMAKE_C_STANDARD 23)

add_executable(fract_ol main.c
        fract_ol.h
        input.c
        render.c
        utils.c
        fractals.c)

target_include_directories(fract_ol PUBLIC ${PROJECT_SOURCE_DIR}/ft_printf)
target_include_directories(fract_ol PUBLIC ${PROJECT_SOURCE_DIR}/ft_printf/libft)

add_library(mlx STATIC IMPORTED)
set_target_properties(mlx PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/libmlx.a)

add_library(ft_printf STATIC IMPORTED)
set_target_properties(ft_printf PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/ft_printf/libftprintf.a)

target_link_libraries(fract_ol mlx ft_printf)

target_link_libraries(fract_ol "-lXext -lX11 -lm -fopenmp")
