/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nova_fractal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 10:58:14 by eebert            #+#    #+#             */
/*   Updated: 2024/10/24 10:58:56 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

static int	nova_helper(t_vec2 *z, t_vec2 *z_temp, t_vec2 *denom, t_complex c)
{
	double	denom_mag;

	denom_mag = denom->x * denom->x + denom->y * denom->y;
	if (denom_mag == 0)
		return (1);
	z_temp->x = (z_temp->x * denom->x + z_temp->y * denom->y) / denom_mag;
	z_temp->y = (z_temp->y * denom->x - z_temp->x * denom->y) / denom_mag;
	z->x = z->x - z_temp->x + c.r;
	z->y = z->y - z_temp->y + c.i;
	if (z->x * z->x + z->y * z->y > 4)
		return (1);
	return (0);
}

int	in_set_nova(double x, double y, t_fractal *data)
{
	int			i;
	t_complex	c;
	t_vec2		z;
	t_vec2		z_temp;
	t_vec2		denom;

	i = 0;
	c.r = data->c.r;
	c.i = data->c.i;
	z.x = x;
	z.y = y;
	while (i < data->max_iter)
	{
		z_temp.x = z.x * z.x - z.y * z.y;
		z_temp.y = 2.0 * z.x * z.y;
		denom.x = z_temp.x * z_temp.x - z_temp.y * z_temp.y;
		denom.y = 2.0 * z_temp.x * z_temp.y;
		if (nova_helper(&z, &z_temp, &denom, c))
			break ;
		i++;
	}
	return (i);
}
