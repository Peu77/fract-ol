/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:42:33 by eebert            #+#    #+#             */
/*   Updated: 2024/10/24 11:04:26 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"
#include "ft_printf.h"
#include "libft.h"

static int	handle_flags(char flag, char **argv, int *i, t_fractal *data)
{
	if (flag == 'i')
	{
		if (argv[*i + 1] == 0)
			return (0);
		data->max_iter = ft_atoi(argv[*i + 1]);
		(*i)++;
	}
	else if (flag == 'c')
	{
		if (argv[*i + 1] == 0 || argv[*i + 2] == 0)
			return (0);
		data->c.r = ft_atof(argv[*i + 1]);
		data->c.i = ft_atof(argv[*i + 2]);
		(*i) += 2;
	}
	else if (flag == 'h')
		return (0);
	else
	{
		ft_printf("Unknown flag: %s\n", argv[*i]);
		return (0);
	}
	return (1);
}

static int	parse_flags_fractal(char **argv, t_fractal *data)
{
	char	flag;
	int		i;

	i = 1;
	while (argv[i])
	{
		if (argv[i][0] != '-' || argv[i][1] == 0)
			return (0);
		flag = argv[i][1];
		if (!handle_flags(flag, argv, &i, data))
			return (0);
		i++;
	}
	return (1);
}

int	parse_args(int argc, char **argv, t_fractal *data)
{
	if (argc <= 0)
		return (0);
	if (ft_strncmp(argv[0], "mandelbrot", sizeof("mandelbrot")) == 0)
	{
		data->in_set = in_set_mandelbrot;
	}
	else if (ft_strncmp(argv[0], "julia", sizeof("julia")) == 0)
	{
		data->in_set = in_set_julia;
		data->c.r = -0.7;
		data->c.i = 0.27015;
	}
	else if (ft_strncmp(argv[0], "burning_ship", sizeof("burning_ship")) == 0)
		data->in_set = in_burning_ship;
	else if (ft_strncmp(argv[0], "nova", sizeof("nova")) == 0)
	{
		data->in_set = in_set_nova;
		data->max_iter = 10;
	}
	else
	{
		ft_printf("Unknown fractal: %s\n", argv[0]);
		return (0);
	}
	return (parse_flags_fractal(argv, data));
}
