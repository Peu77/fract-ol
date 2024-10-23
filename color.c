/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:31:39 by eebert            #+#    #+#             */
/*   Updated: 2024/10/23 20:08:14 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

int get_color(int iter, const int max_iter);

int get_color_black_white(int iter, const int max_iter);

int get_color_red_blue(int iter, const int max_iter);

int get_color_rainbow(int iter, const int max_iter);


t_get_color_func get_next_color_func() {
    static t_get_color_func color_funcs[] = {get_color, get_color_black_white, get_color_red_blue, get_color_rainbow};
    static int i = 0;

    return color_funcs[i++ % 4];
}


int get_color(int iter, const int max_iter) {
    if (iter == max_iter)
        return 0x000000;

    return (int) (iter * 255.0 / max_iter) << 16 | (int) (iter * 255.0 / max_iter) << 8 |
           (int) (iter * 255.0 / max_iter);
}

int get_color_rainbow(int iter, const int max_iter) {
    if (iter == max_iter)
        return 0x000000;

    if (iter < max_iter / 3) {
        return (int) (iter * 255.0 / (max_iter / 3)) << 8;
    } else if (iter < 2 * max_iter / 3) {
        return (int) (255 - (iter - max_iter / 3) * 255.0 / (max_iter / 3)) << 16 | 0x0000FF;
    } else {
        return (int) ((iter - 2 * max_iter / 3) * 255.0 / (max_iter / 3)) << 8 | 0xFF0000;
    }
}

int get_color_red_blue(int iter, const int max_iter) {
    if (iter == 0) {
        return 0x000000;
    }
    if (iter < max_iter / 2) {
        return (int) (iter * 255.0 / (max_iter / 2)) << 16;
    } else {
        return (int) (255 - (iter - max_iter / 2) * 255.0 / (max_iter / 2)) << 8;
    }
}


int get_color_black_white(int iter, const int max_iter) {
    if (iter == 0)
        return 0x000000;

    if (iter % 2 == 0) {
        return 0x000000;
    } else {
        return 0xFFFFFF;
    }
}