/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:27:17 by eebert            #+#    #+#             */
/*   Updated: 2024/10/24 10:58:37 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"
#include <math.h>
#include <stdio.h>

void	init_fractal(t_fractal *data)
{
	data->c.r = 0;
	data->c.i = 0;
	data->max_iter = 100;
}

void	apply_color_of_fractal_at_pos(t_render_data *render_data, t_vec2 index,
		t_vec2 z)
{
	const int	offset = render_data->fractal->in_set(z.x, z.y,
			render_data->fractal);
	const int	color = render_data->get_color_func(offset,
			render_data->fractal->max_iter);
	const int	pixel = (index.y * render_data->size_line) + (index.x
			* (render_data->bits_per_pixel / 8));

	render_data->img_data[pixel] = color;
	render_data->img_data[pixel + 1] = color >> 8;
	render_data->img_data[pixel + 2] = color >> 16;
}

int	in_set_mandelbrot(double x, double y, t_fractal *data)
{
	int		i;
	t_vec2	c;
	t_vec2	z;
	t_vec2	z_temp;

	i = 0;
	c.x = x;
	c.y = y;
	z.x = 0;
	z.y = 0;
	while (i < data->max_iter)
	{
		z_temp.x = z.x * z.x - z.y * z.y + c.x;
		z_temp.y = 2.0 * z.x * z.y + c.y;
		z.x = z_temp.x;
		z.y = z_temp.y;
		if (z.x * z.x + z.y * z.y > 4)
		{
			return (i);
		}
		i++;
	}
	return (i);
}

int	in_set_julia(double x, double y, t_fractal *data)
{
	int		i;
	double	x0;
	double	y0;

	i = 0;
	while (i < data->max_iter)
	{
		x0 = x * x - y * y + data->c.r;
		y0 = 2.0 * x * y + data->c.i;
		x = x0;
		y = y0;
		if (x * x + y * y > 4)
		{
			return (i);
		}
		i++;
	}
	return (i);
}

int	in_burning_ship(double x, double y, t_fractal *data)
{
	int		i;
	double	cx;
	double	cy;
	double	x0;
	double	y0;

	i = 0;
	cx = x;
	cy = y;
	x = 0;
	y = 0;
	while (i < data->max_iter)
	{
		x0 = x * x - y * y + cx;
		y0 = 2.0 * fabs(x * y) + cy;
		x = fabs(x0);
		y = fabs(y0);
		if (x * x + y * y > 4)
		{
			return (i);
		}
		i++;
	}
	return (i);
}
