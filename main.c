/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:59:22 by eebert            #+#    #+#             */
/*   Updated: 2024/10/22 15:22:23 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "mlx.h"
#include <pthread.h>
#include "fract_ol.h"

#define MAX_ITER 100

int is_in_set(double x, double y, double cX, double cY) {
    double x0, y0;
    int i = 0;

    while (i < MAX_ITER) {
        x0 = x * x - y * y + cX;
        y0 = 2.0 * x * y + cY;
        x = x0;
        y = y0;
        if (x * x + y * y > 4) {
            break;
        }
        i++;
    }
    return i;
}

int is_in_set_mandelbrot(double x, double y) {
    double x0, y0;
    int i = 0;

    double cX = x;
    double cY = y;
    x = 0;
    y = 0;

    while (i < MAX_ITER) {
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

int get_color(int iter) {
    if (iter == MAX_ITER)
        return 0x000000; // black

    // Create a gradient from black to white
    return (int) (iter * 255.0 / MAX_ITER) << 16 | (int) (iter * 255.0 / MAX_ITER) << 8 |
           (int) (iter * 255.0 / MAX_ITER);

}

int get_color_black_white(int iter) {
    if (iter == MAX_ITER) {
        return 0xFF0000;
    }

    if (iter < MAX_ITER - 2) {
        if (iter % 2 == 0) {
            return 0x000000;
        } else {
            return 0xFFFFFF;
        }
    }
    if (iter == MAX_ITER - 2) {
        return 0x000000;
    }

    return 0xFFFFFF;

    if (iter == MAX_ITER)
        return 0x000000; // black

    return 0xFFFFFF; // white
}


int main(int argc, char **argv) {
    t_fractal fractal;
    t_render_data render_data;

    init_fractal(&fractal);
    if(!parse_args(--argc, ++argv, &fractal)){
        return 1;
    }

    render_data.fractal = &fractal;
    init_render_data(&render_data);
    mlx_loop(render_data.mlx);
    return 0;
}