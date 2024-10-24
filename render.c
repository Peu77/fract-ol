/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:46:11 by eebert            #+#    #+#             */
/*   Updated: 2024/10/24 11:19:02 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"
#include "mlx.h"
#include <math.h>
#include <pthread.h>
#include <stdio.h>

static void	draw_fractal(t_render_data *render_data)
{
	t_vec2	z;
	t_vec2	index;

	index.x = 0;
	while (index.x < WIDTH)
	{
		z.x = (render_data->max_x - render_data->min_x) * index.x / WIDTH
			+ render_data->min_x;
		index.y = 0;
		while (index.y < HEIGHT)
		{
			z.y = (render_data->max_y - render_data->min_y) * index.y / HEIGHT
				+ render_data->min_y;
			apply_color_of_fractal_at_pos(render_data, index, z);
			index.y++;
		}
		index.x++;
	}
}

static int	draw_next_frame(void *data)
{
	t_render_data	*render_data;
	static double	last_render_min_x;
	static double	last_render_min_y;

	render_data = (t_render_data *)data;
	if (last_render_min_x != render_data->min_x
		|| last_render_min_y != render_data->min_y || render_data->update_frame)
		draw_fractal(render_data);
	last_render_min_x = render_data->min_x;
	last_render_min_y = render_data->min_y;
	render_data->update_frame = false;
	mlx_put_image_to_window(render_data->mlx, render_data->win,
		render_data->img, 0, 0);
	draw_custom_cursor(render_data->mlx, render_data->win);
	draw_help_text(render_data);
	return (0);
}

void	init_render_data(t_render_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, TITLE);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img_data = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->size_line, &data->endian);
	data->get_color_func = get_next_color_func();
	data->update_frame = false;
	mlx_loop_hook(data->mlx, (int (*)(void))draw_next_frame, data);
	data->min_x = -2.0;
	data->max_x = 2.0;
	data->min_y = -2.0;
	data->max_y = 2.0;
}
