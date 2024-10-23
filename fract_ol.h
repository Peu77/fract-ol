/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:30:11 by eebert            #+#    #+#             */
/*   Updated: 2024/10/23 21:39:47 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

#include <stdbool.h>

#define WIDTH 1000
#define HEIGHT 900
#define TITLE "Fractol"

#define ARROW_RIGHT 65363
#define ARROW_LEFT 65361
#define ARROW_UP 65362
#define ARROW_DOWN 65364

typedef int (*t_get_color_func)(int, const int);

t_get_color_func get_next_color_func();

struct s_fractal;

typedef int (*t_fractal_in_set)(double, double, struct s_fractal *);

typedef struct s_complex {
    double r;
    double i;
} t_complex;

typedef struct s_fractal {
    struct s_complex c;
    int max_iter;

    t_fractal_in_set in_set;
} t_fractal;

typedef struct s_render_data {
    void *mlx;
    void *win;
    void *img;
    char *img_data;
    int bits_per_pixel;
    int size_line;
    int endian;
    double min_x;
    double max_x;
    double min_y;
    double max_y;
    t_fractal *fractal;
    t_get_color_func get_color_func;
    bool update_frame;
} t_render_data;


void init_fractal(t_fractal *data);

void init_render_data(t_render_data *data);

int parse_args(int argc, char **argv, t_fractal *data);

int in_set_mandelbrot(double x, double y, t_fractal *data);

int in_set_julia(double x, double y, t_fractal *data);

int in_burning_ship(double x, double y, t_fractal *data);

int in_set_nova(double x, double y, t_fractal *data);

int mouse_hook(int button, int x, int y, void *param);

int key_hook(int key, void *param);

// utils

float ft_atof(const char *str);

# endif