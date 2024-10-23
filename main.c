/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:59:22 by eebert            #+#    #+#             */
/*   Updated: 2024/10/23 12:51:20 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fract_ol.h"


int main(int argc, char **argv) {
    t_fractal fractal;
    t_render_data render_data;

    init_fractal(&fractal);
    if (!parse_args(--argc, ++argv, &fractal)) {
        return 1;
    }

    render_data.fractal = &fractal;
    init_render_data(&render_data);
    mlx_mouse_hook(render_data.win, (int (*)(void)) mouse_hook, &render_data);
    mlx_key_hook(render_data.win, (int (*)(void)) key_hook, &render_data);
    mlx_loop(render_data.mlx);
    return 0;
}