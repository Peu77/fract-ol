/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:46:11 by eebert            #+#    #+#             */
/*   Updated: 2024/10/22 16:12:16 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"
#include "mlx.h"
#include <pthread.h>
#include <stdio.h>
#include <omp.h>

static int mouse_hook(int button, int x, int y, void *param) {
    t_render_data *render_data = (t_render_data *) param;
    double zoom_factor = 1.1;

    double mouse_x = (double)x / WIDTH * (render_data->max_x - render_data->min_x) + render_data->min_x;
    double mouse_y = (double)y / HEIGHT * (render_data->max_y - render_data->min_y) + render_data->min_y;

    if (button == 4) {
        render_data->min_x = mouse_x + (render_data->min_x - mouse_x) / zoom_factor;
        render_data->max_x = mouse_x + (render_data->max_x - mouse_x) / zoom_factor;
        render_data->min_y = mouse_y + (render_data->min_y - mouse_y) / zoom_factor;
        render_data->max_y = mouse_y + (render_data->max_y - mouse_y) / zoom_factor;
    } else if (button == 5) {
        render_data->min_x = mouse_x + (render_data->min_x - mouse_x) * zoom_factor;
        render_data->max_x = mouse_x + (render_data->max_x - mouse_x) * zoom_factor;
        render_data->min_y = mouse_y + (render_data->min_y - mouse_y) * zoom_factor;
        render_data->max_y = mouse_y + (render_data->max_y - mouse_y) * zoom_factor;
    }

    printf("min_x: %f, max_x: %f, min_y: %f, max_y: %f\n", render_data->min_x, render_data->max_x, render_data->min_y, render_data->max_y);
    return 0;
}

static int draw_next_frame(void *data) {
    t_render_data *render_data = (t_render_data *) data;


#pragma omp parallel for
    for (int x = 0; x < WIDTH; x++) {
        double zx = (render_data->max_x - render_data->min_x) * x / WIDTH + render_data->min_x;
#pragma omp parallel for
        for (int y = 0; y < HEIGHT; y++) {
            double zy = (render_data->max_y - render_data->min_y) * y / HEIGHT + render_data->min_y;

            int offset = render_data->fractal->in_set(zx, zy, render_data->fractal);
            int color = get_color(offset);
            int pixel = (y * render_data->size_line) + (x * (render_data->bits_per_pixel / 8));

            render_data->img_data[pixel] = color;
            render_data->img_data[pixel + 1] = color >> 8;
            render_data->img_data[pixel + 2] = color >> 16;
        }
    }

    mlx_put_image_to_window(render_data->mlx, render_data->win, render_data->img, 0, 0);

    return 0;
}

void init_render_data(t_render_data *data) {
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, TITLE);
    data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->img_data = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->size_line, &data->endian);

    mlx_loop_hook(data->mlx, (int (*)(void)) draw_next_frame, data);
    mlx_mouse_hook(data->win, (int (*)(void)) mouse_hook, data);
    data->min_x = -2.0;
    data->max_x = 2.0;
    data->min_y = -2.0;
    data->max_y = 2.0;
}