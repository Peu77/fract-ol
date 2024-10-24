/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 10:23:47 by eebert            #+#    #+#             */
/*   Updated: 2024/10/24 11:19:26 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"
#include "mlx.h"

void	draw_help_text(t_render_data *render_data)
{
	mlx_string_put(render_data->mlx, render_data->win, 10, 10, 0xFFFFFF,
		"Press space to change color function");
	mlx_string_put(render_data->mlx, render_data->win, 10, 30, 0xFFFFFF,
		"Use mouse wheel to zoom in/out");
	mlx_string_put(render_data->mlx, render_data->win, 10, 50, 0xFFFFFF,
		"Use arrow keys to move");
	mlx_string_put(render_data->mlx, render_data->win, 10, 70, 0xFFFFFF,
		"Use Escape to quit");
}

#ifdef CUSTOM_CURSOR

static int	get_color_cursor(int x, int y)
{
	return (((int)(sin(x) * 255 + sin(y) * 255) << 16) | ((int)(sin(x) * 255
				+ sin(y) * 255) << 8) | (int)(sin(x) * 255 + sin(y) * 255));
}

void	draw_custom_cursor(void *mlx, void *win)
{
	const int	radius = 5;
	t_vec2i		mouse;
	int			i;
	int			j;

	mlx_mouse_get_pos(win, &mouse.x, &mouse.y);
	if (mouse.x < 0 || mouse.x >= WIDTH || mouse.y < 0 || mouse.y >= HEIGHT)
		return ;
	i = -radius;
	while (i <= radius)
	{
		j = -radius;
		while (j <= radius)
		{
			if (i * i + j * j <= radius * radius)
				mlx_pixel_put(mlx, win, mouse.x + i, mouse.y + j,
					get_color_cursor(mouse.x + i, mouse.y + j));
			j++;
		}
		i++;
	}
}
#endif

#ifndef CUSTOM_CURSOR

void	draw_custom_cursor(void *mlx, void *win)
{
	(void)mlx;
	(void)win;
}

#endif
