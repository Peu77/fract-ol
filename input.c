/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:42:33 by eebert            #+#    #+#             */
/*   Updated: 2024/10/22 13:45:19 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"
#include "libft.h"

int parse_args(int argc, char **argv, t_fractal *data) {
    if (argc != 2) {
        return 1;
    }
    if (ft_strncmp(argv[1], "mandelbrot", sizeof("mandelbrot")) == 0) {
        data->c.r = 0;
        data->c.i = 0;
        data->min_x = -2.0;
        data->max_x = 2.0;
        data->max_iter = 100;
        return 0;
    }
    if (ft_strcmp(argv[1], "julia") == 0) {
        data->c.r = -0.7;
        data->c.i = 0.27015;
        data->min_x = -2.0;
        data->max_x = 2.0;
        data->max_iter = 100;
        return 0;
    }
    return 1;
}