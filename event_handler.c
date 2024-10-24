/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:36:00 by eebert            #+#    #+#             */
/*   Updated: 2024/10/23 21:54:12 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"
#include <stdio.h>
#include <stdlib.h>
#include "mlx.h"

void safe_exit(t_render_data* render_data)
{
    if(!render_data->mlx)
        exit(1);

    if (render_data->win)
        mlx_destroy_window(render_data->mlx, render_data->win);
    if (render_data->img)
        mlx_destroy_image(render_data->mlx, render_data->img);

    exit(0);
}

int mouse_hook(int button, int x, int y, void* param)
{
    t_render_data* render_data = (t_render_data*)param;
    double zoom_factor = 1.1;

    double mouse_x = (double)x / WIDTH * (render_data->max_x - render_data->min_x) + render_data->min_x;
    double mouse_y = (double)y / HEIGHT * (render_data->max_y - render_data->min_y) + render_data->min_y;

    if (button == 4)
    {
        render_data->min_x = mouse_x + (render_data->min_x - mouse_x) / zoom_factor;
        render_data->max_x = mouse_x + (render_data->max_x - mouse_x) / zoom_factor;
        render_data->min_y = mouse_y + (render_data->min_y - mouse_y) / zoom_factor;
        render_data->max_y = mouse_y + (render_data->max_y - mouse_y) / zoom_factor;
    }
    else if (button == 5)
    {
        render_data->min_x = mouse_x + (render_data->min_x - mouse_x) * zoom_factor;
        render_data->max_x = mouse_x + (render_data->max_x - mouse_x) * zoom_factor;
        render_data->min_y = mouse_y + (render_data->min_y - mouse_y) * zoom_factor;
        render_data->max_y = mouse_y + (render_data->max_y - mouse_y) * zoom_factor;
    }

    return 0;
}

int key_hook(int key, void* param)
{
    t_render_data* render_data = (t_render_data*)param;

    if (key == SPACE)
    {
        render_data->get_color_func = get_next_color_func();
        render_data->update_frame = true;
        return 0;
    }

    if (key == ESC)
        safe_exit(render_data);

    int up = 0;
    int right = 0;

    if (key == ARROW_RIGHT)
        right = 1;
    else if (key == ARROW_LEFT)
        right = -1;
    else if (key == ARROW_UP)
        up = 1;
    else if (key == ARROW_DOWN)
        up = -1;


    double dx = (render_data->max_x - render_data->min_x) / 10;
    double dy = (render_data->min_y - render_data->max_y) / 10;

    render_data->min_x += dx * right;
    render_data->max_x += dx * right;
    render_data->min_y += dy * up;
    render_data->max_y += dy * up;
    return 0;
}
