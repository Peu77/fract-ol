cmake_minimum_required(VERSION 3.27)
project(fract_ol C)

set(CMAKE_C_STANDARD 23)

add_executable(fract_ol main.c)

add_library(mlx STATIC IMPORTED)
set_target_properties(mlx PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/libmlx.a)

target_link_libraries(fract_ol mlx)

target_link_libraries(fract_ol "-lXext -lX11 -lm -fopenmp")
