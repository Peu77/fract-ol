/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:59:22 by eebert            #+#    #+#             */
/*   Updated: 2024/10/24 10:07:04 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"
#include "ft_printf.h"
#include "mlx.h"

static void	send_help(void)
{
	ft_printf("Usage: fractol [fractal] [flags]\n");
	ft_printf("Fractals:\n");
	ft_printf("mandelbrot\n");
	ft_printf("burning_ship\n");
	ft_printf("julia\n");
	ft_printf("nova\n");
	ft_printf("Flags:\n");
	ft_printf("%-20s -> print help\n", "-h");
	ft_printf("%-20s -> set the max iteration count\n", "-i [nb]");
	ft_printf("%-20s -> set the complex number\n", "-c [nb.r] [nb.i]");
}

int	main(int argc, char **argv)
{
	t_fractal		fractal;
	t_render_data	render_data;

	init_fractal(&fractal);
	if (!parse_args(--argc, ++argv, &fractal))
	{
		send_help();
		return (1);
	}
	render_data.fractal = &fractal;
	init_render_data(&render_data);
	if (!render_data.mlx)
		safe_exit(&render_data);
	mlx_mouse_hook(render_data.win, (int (*)(void))mouse_hook, &render_data);
	mlx_key_hook(render_data.win, (int (*)(void))key_hook, &render_data);
	mlx_hook(render_data.win, 17, 0, (int (*)(void))safe_exit, &render_data);
	mlx_loop(render_data.mlx);
	return (0);
}
