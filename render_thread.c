/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:46:11 by eebert            #+#    #+#             */
/*   Updated: 2024/10/24 10:31:08 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"
#include "mlx.h"
#include <pthread.h>
#include <stdio.h>

typedef struct s_thread_data
{
	t_render_data	*render_data;
	int				start_x;
	int				end_x;
}					t_thread_data;

void	*draw_section(void *arg)
{
	t_thread_data	*thread_data;
	t_render_data	*render_data;
	t_vec2			z;
	t_vec2			index;

	thread_data = (t_thread_data *)arg;
	render_data = thread_data->render_data;
	index.x = thread_data->start_x;
	while (index.x < thread_data->end_x)
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
	return (NULL);
}

static void	init_threads(t_thread_data *thread_data, t_render_data *render_data,
		pthread_t *threads)
{
	int	section_width;
	int	i;

	section_width = WIDTH / NUM_THREADS;
	i = 0;
	while (i < NUM_THREADS)
	{
		thread_data[i].render_data = render_data;
		thread_data[i].start_x = i * section_width;
		thread_data[i].end_x = (i + 1) * section_width;
		pthread_create(&threads[i], NULL, draw_section, &thread_data[i]);
		i++;
	}
	i = 0;
	while (i < NUM_THREADS)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

static int	draw_next_frame(void *data)
{
	t_render_data	*render_data;
	static double	last_render_min_x;
	static double	last_render_min_y;
	pthread_t		threads[NUM_THREADS];
	t_thread_data	thread_data[NUM_THREADS];

	render_data = (t_render_data *)data;
	if (last_render_min_x == render_data->min_x
		&& last_render_min_y == render_data->min_y
		&& !render_data->update_frame)
	{
		return (0);
	}
	last_render_min_x = render_data->min_x;
	last_render_min_y = render_data->min_y;
	render_data->update_frame = false;
	init_threads(thread_data, render_data, threads);
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
