/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:46:11 by eebert            #+#    #+#             */
/*   Updated: 2024/10/23 13:36:34 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"
#include "mlx.h"
#include <pthread.h>
#include <stdio.h>
#include <omp.h>

static int draw_next_frame(void *data) {
    t_render_data *render_data = (t_render_data *) data;
    static double last_render_min_x;
    static double last_render_min_y;

    if (last_render_min_x == render_data->min_x && last_render_min_y == render_data->min_y &&
        !render_data->update_frame) {
        return 0;
    }

    last_render_min_x = render_data->min_x;
    last_render_min_y = render_data->min_y;
    render_data->update_frame = false;

#pragma omp parallel for
    for (int x = 0; x < WIDTH; x++) {
        double zx = (render_data->max_x - render_data->min_x) * x / WIDTH + render_data->min_x;
#pragma omp parallel for
        for (int y = 0; y < HEIGHT; y++) {
            double zy = (render_data->max_y - render_data->min_y) * y / HEIGHT + render_data->min_y;

            int offset = render_data->fractal->in_set(zx, zy, render_data->fractal);
            int color = render_data->get_color_func(offset, render_data->fractal->max_iter);
            int pixel = (y * render_data->size_line) + (x * (render_data->bits_per_pixel / 8));

            render_data->img_data[pixel] = color;
            render_data->img_data[pixel + 1] = color >> 8;
            render_data->img_data[pixel + 2] = color >> 16;
        }
    }

    mlx_put_image_to_window(render_data->mlx, render_data->win, render_data->img, 0, 0);

    mlx_string_put(render_data->mlx, render_data->win, 10, 10, 0xFFFFFF, "Press space to change color function");

    return 0;
}

void init_render_data(t_render_data *data) {
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, TITLE);
    data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->img_data = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->size_line, &data->endian);
    data->get_color_func = get_next_color_func();
    data->update_frame = false;

    mlx_loop_hook(data->mlx, (int (*)(void)) draw_next_frame, data);
    data->min_x = -2.0;
    data->max_x = 2.0;
    data->min_y = -2.0;
    data->max_y = 2.0;
}