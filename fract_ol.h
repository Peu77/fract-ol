/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:30:11 by eebert            #+#    #+#             */
/*   Updated: 2024/10/22 13:49:30 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

#define WIDTH 1000
#define HEIGHT 900

typedef struct s_complex {
    double r;
    double i;
} t_complex;

typedef struct s_fractal {
    struct s_complex c;
    double min_x;
    double max_x;
    int max_iter;
    int bits_per_pixel;
    int size_line;
    int endian;
} t_fractal;

typedef struct s_render_data {
    void *mlx;
    void *win;
    char *img;
    t_fractal *data;
} t_render_data;

typedef int (*t_fractal_in_set)(double, double, t_fractal *);

void init_render_data(t_fractal *data);

int parse_args(int argc, char **argv, t_fractal *data);

# endif