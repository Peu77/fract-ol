/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:30:11 by eebert            #+#    #+#             */
/*   Updated: 2024/10/22 15:39:56 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

#define WIDTH 1000
#define HEIGHT 900
#define TITLE "Fractol"

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
    float zoom;
    t_fractal *fractal;
} t_render_data;


void init_fractal(t_fractal *data);

void init_render_data(t_render_data *data);

int parse_args(int argc, char **argv, t_fractal *data);

int in_set_mandelbrot(double x, double y, t_fractal *data);

int in_set_julia(double x, double y, t_fractal *data);

int get_color(int iter);

// utils

float ft_atof(const char *str);

# endif