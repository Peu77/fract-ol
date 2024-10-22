/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:27:17 by eebert            #+#    #+#             */
/*   Updated: 2024/10/22 14:27:17 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

int in_set_mandelbrot(double x, double y, t_fractal *data) {
    double x0, y0;
    int i = 0;

    double cX = x;
    double cY = y;
    x = 0;
    y = 0;

    while (i < data->max_iter) {
        x0 = x * x - y * y + cX;
        y0 = 2.0 * x * y + cY;
        x = x0;
        y = y0;
        if (x * x + y * y > 4) {
            return i;
        }
        i++;
    }
    return i;
}

int in_set_julia(double x, double y, t_fractal *data) {
    double x0, y0;
    int i = 0;

    while (i < data->max_iter) {
        x0 = x * x - y * y + data->c.r;
        y0 = 2.0 * x * y + data->c.i;
        x = x0;
        y = y0;
        if (x * x + y * y > 4) {
            return i;
        }
        i++;
    }
    return i;
}