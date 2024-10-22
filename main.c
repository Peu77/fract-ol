/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:59:22 by eebert            #+#    #+#             */
/*   Updated: 2024/10/22 13:11:11 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "mlx.h"
#include <pthread.h>

#define WIDTH 1000
#define HEIGHT 900
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

double zoom = 1.0;
double last_rendered_zoom = 0.0;
double offsetX = 0.0;
double offsetY = 0.0;

int mouse_hook(int button, int x, int y, void *param) {

    double mouseX = (x - WIDTH / 2) / (0.5 * WIDTH * zoom) + offsetX;
    double mouseY = (y - HEIGHT / 2) / (0.5 * HEIGHT * zoom) + offsetY;

    if (button == 1) {
        zoom = 1.0;
        offsetX = 0.0;
        offsetY = 0.0;
    } else if (button == 4) {
        zoom *= 1.1;
        offsetX = mouseX - (x - WIDTH / 2) / (0.5 * WIDTH * zoom);
        offsetY = mouseY - (y - HEIGHT / 2) / (0.5 * HEIGHT * zoom);
    } else if (button == 5) {
        zoom /= 1.1;
        offsetX = mouseX - (x - WIDTH / 2) / (0.5 * WIDTH * zoom);
        offsetY = mouseY - (y - HEIGHT / 2) / (0.5 * HEIGHT * zoom);
    }
    return 0;
}

int bits_per_pixel;
int size_line;
int endian;
char *data;
void *img;
void *mlx;
void *win;

typedef struct {
    int start;
    int end;
    double inv_zoom;
    double inv_zoom_height;
    char *img;
} thread_data_t;

void *render_section(void *arg) {
    thread_data_t *data = (thread_data_t *) arg;
    for (int x = data->start; x < data->end; x++) {
        double zx = (x - WIDTH / 2) * data->inv_zoom + offsetX;
        for (int y = 0; y < HEIGHT; y++) {
            double zy = (y - HEIGHT / 2) * data->inv_zoom_height + offsetY;

            int offset = is_in_set_mandelbrot(zx, zy);
            int color = get_color(offset);
            int pixel = (y * size_line) + (x * (bits_per_pixel / 8));
            data->img[pixel] = color;
            data->img[pixel + 1] = color >> 8;
            data->img[pixel + 2] = color >> 16;
        }
    }
    return NULL;
}

int render_next_frame() {
    if (last_rendered_zoom == zoom) {
        return 0;
    }

    time_t start;
    time_t end;

    double inv_zoom = 1.0 / (0.5 * WIDTH * zoom);
    double inv_zoom_height = 1.0 / (0.5 * HEIGHT * zoom);

    int num_threads = 50; // Number of threads
    pthread_t threads[num_threads];
    thread_data_t thread_data[num_threads];

    int section_width = WIDTH / num_threads;

    time(&start);

    for (int i = 0; i < num_threads; i++) {
        thread_data[i].start = i * section_width;
        thread_data[i].end = (i + 1) * section_width;
        thread_data[i].inv_zoom = inv_zoom;
        thread_data[i].inv_zoom_height = inv_zoom_height;
        thread_data[i].img = data;
        pthread_create(&threads[i], NULL, render_section, &thread_data[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    last_rendered_zoom = zoom;
    mlx_put_image_to_window(mlx, win, img, 0, 0);
    time(&end);

    printf("Time taken: %.2fs\n", difftime(end, start));
    return 0;
}

int main(void) {
    mlx = mlx_init();
    win = mlx_new_window(mlx, WIDTH, HEIGHT, "Fractol");

    img = mlx_new_image(mlx, WIDTH, HEIGHT);
    data = (char *) mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);

    mlx_mouse_hook(win, (int (*)(void)) mouse_hook, NULL);
    mlx_loop_hook(mlx, (int (*)(void)) render_next_frame, NULL);

    mlx_loop(mlx);
    return 0;
}