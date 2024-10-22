/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:46:11 by eebert            #+#    #+#             */
/*   Updated: 2024/10/22 15:40:16 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"
#include "mlx.h"
#include <pthread.h>
#include <stdio.h>

static int draw_next_frame(void *data) {
    t_render_data *render_data = (t_render_data *) data;
    double inv_zoom = 1.0 / (0.5 * WIDTH * render_data->zoom);
    double inv_zoom_height = 1.0 / (0.5 * HEIGHT * render_data->zoom);


    for (int x = 0; x < WIDTH; x++) {
        double zx = (x - WIDTH / 2) * inv_zoom;
        for (int y = 0; y < HEIGHT; y++) {
            double zy = (y - HEIGHT / 2) * inv_zoom_height;

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
    data->min_x = -2.0;
    data->max_x = 2.0;
    data->zoom = 1.0f;
}