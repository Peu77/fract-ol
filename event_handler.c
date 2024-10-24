/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:36:00 by eebert            #+#    #+#             */
/*   Updated: 2024/10/24 10:40:29 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

void	safe_exit(t_render_data *render_data)
{
	if (!render_data->mlx)
		exit(1);
	if (render_data->win)
		mlx_destroy_window(render_data->mlx, render_data->win);
	if (render_data->img)
		mlx_destroy_image(render_data->mlx, render_data->img);
	exit(0);
}

static void	apply_zoom(t_render_data *render_data, double mouse_x,
		double mouse_y, double zoom_factor)
{
	render_data->min_x = mouse_x + (render_data->min_x - mouse_x) * zoom_factor;
	render_data->max_x = mouse_x + (render_data->max_x - mouse_x) * zoom_factor;
	render_data->min_y = mouse_y + (render_data->min_y - mouse_y) * zoom_factor;
	render_data->max_y = mouse_y + (render_data->max_y - mouse_y) * zoom_factor;
}

int	mouse_hook(int button, int x, int y, void *param)
{
	t_render_data	*render_data;
	double			zoom_factor;
	double			mouse_x;
	double			mouse_y;

	render_data = (t_render_data *)param;
	zoom_factor = 1.1;
	mouse_x = (double)x / WIDTH * (render_data->max_x - render_data->min_x)
		+ render_data->min_x;
	mouse_y = (double)y / HEIGHT * (render_data->max_y - render_data->min_y)
		+ render_data->min_y;
	if (button == 4)
	{
		apply_zoom(render_data, mouse_x, mouse_y, 1 / zoom_factor);
		render_data->update_frame = true;
	}
	else if (button == 5)
	{
		apply_zoom(render_data, mouse_x, mouse_y, zoom_factor);
		render_data->update_frame = true;
	}
	return (0);
}

static void	handle_arrow_movement(int key, t_render_data *render_data)
{
	int		up;
	int		right;
	double	dx;
	double	dy;

	up = 0;
	right = 0;
	if (key == ARROW_RIGHT)
		right = 1;
	else if (key == ARROW_LEFT)
		right = -1;
	else if (key == ARROW_UP)
		up = 1;
	else if (key == ARROW_DOWN)
		up = -1;
	dx = (render_data->max_x - render_data->min_x) / 10;
	dy = (render_data->min_y - render_data->max_y) / 10;
	render_data->min_x += dx * right;
	render_data->max_x += dx * right;
	render_data->min_y += dy * up;
	render_data->max_y += dy * up;
}

int	key_hook(int key, void *param)
{
	t_render_data	*render_data;
	int				up;
	int				right;
	double			dx;
	double			dy;

	render_data = (t_render_data *)param;
	if (key == SPACE)
	{
		render_data->get_color_func = get_next_color_func();
		render_data->update_frame = true;
		return (0);
	}
	if (key == ESC)
		safe_exit(render_data);
	if (key == ARROW_UP || key == ARROW_DOWN || key == ARROW_LEFT
		|| key == ARROW_RIGHT)
		handle_arrow_movement(key, render_data);
	return (0);
}
