/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:27:17 by eebert            #+#    #+#             */
/*   Updated: 2024/10/23 15:07:30 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "fract_ol.h"

void init_fractal(t_fractal *data){
    data->c.r = 0;
    data->c.i = 0;
    data->max_iter = 50;
}

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

int in_burning_ship(double x, double y, t_fractal *data) {
    double x0, y0;
    int i = 0;

    double cX = x;
    double cY = y;
    x = 0;
    y = 0;

    while (i < data->max_iter) {
        x0 = x * x - y * y + cX;
        y0 = 2.0 * fabs(x * y) + cY;
        x = fabs(x0);
        y = fabs(y0);
        if (x * x + y * y > 4) {
            return i;
        }
        i++;
    }
    return i;
}

int in_set_nova(double x, double y, t_fractal *data) {
    double x0, y0, x_temp, y_temp;
    int i = 0;
    double cX = data->c.r;
    double cY = data->c.i;

    while (i < data->max_iter) {
        // f(z) = z^3 - 1
        // f'(z) = 3z^2
        x0 = x * x * x - 3 * x * y * y - 1;
        y0 = 3 * x * x * y - y * y * y;

        // f'(z)
        x_temp = 3 * (x * x - y * y);
        y_temp = 6 * x * y;

        // z = z - f(z) / f'(z) + c
        double denom = x_temp * x_temp + y_temp * y_temp;
        if (denom == 0) break; // Avoid division by zero

        x_temp = (x0 * x_temp + y0 * y_temp) / denom;
        y_temp = (y0 * x_temp - x0 * y_temp) / denom;

        x = x - x_temp + cX;
        y = y - y_temp + cY;

        if (x * x + y * y > 4) {
            return i;
        }
        i++;
    }
    return i;
}