/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:30:11 by eebert            #+#    #+#             */
/*   Updated: 2024/10/22 13:34:10 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

#define WIDTH 1000
#define HEIGHT 900

typedef struct s_render_data {
    double min_x;
    double max_x;
    int max_iter;
    char *img;
    int bits_per_pixel;
    int size_line;
    int endian;
} t_render_data;

typedef int (*t_fractal)(double, double, t_render_data *);

# endif