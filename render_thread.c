/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:46:11 by eebert            #+#    #+#             */
/*   Updated: 2024/10/23 21:16:43 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"
#include "mlx.h"
#include <pthread.h>
#include <stdio.h>
#include <omp.h>

typedef struct s_thread_data {
    t_render_data *render_data;
    int start_x;
    int end_x;
} t_thread_data;

void *draw_section(void *arg) {
    t_thread_data *thread_data = (t_thread_data *)arg;
    t_render_data *render_data = thread_data->render_data;

    for (int x = thread_data->start_x; x < thread_data->end_x; x++) {
        double zx = (render_data->max_x - render_data->min_x) * x / WIDTH + render_data->min_x;
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

    return NULL;
}

static int draw_next_frame(void *data) {
    t_render_data *render_data = (t_render_data *)data;
    static double last_render_min_x;
    static double last_render_min_y;

    if (last_render_min_x == render_data->min_x && last_render_min_y == render_data->min_y &&
        !render_data->update_frame) {
        return 0;
    }

    last_render_min_x = render_data->min_x;
    last_render_min_y = render_data->min_y;
    render_data->update_frame = false;

    int num_threads = 16;
    pthread_t threads[num_threads];
    t_thread_data thread_data[num_threads];

    int section_width = WIDTH / num_threads;

    for (int i = 0; i < num_threads; i++) {
        thread_data[i].render_data = render_data;
        thread_data[i].start_x = i * section_width;
        thread_data[i].end_x = (i == num_threads - 1) ? WIDTH : (i + 1) * section_width;
        pthread_create(&threads[i], NULL, draw_section, &thread_data[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    mlx_put_image_to_window(render_data->mlx, render_data->win, render_data->img, 0, 0);

    mlx_string_put(render_data->mlx, render_data->win, 10, 10, 0xFFFFFF, "Press space to change color function");
    mlx_string_put(render_data->mlx, render_data->win, 10, 30, 0xFFFFFF, "Use mouse wheel to zoom in/out");
    mlx_string_put(render_data->mlx, render_data->win, 10, 50, 0xFFFFFF, "Use arrow keys to move");
    mlx_string_put(render_data->mlx, render_data->win, 10, 70, 0xFFFFFF, "Use Escape to quit");

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