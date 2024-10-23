/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:31:39 by eebert            #+#    #+#             */
/*   Updated: 2024/10/23 12:56:28 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

int get_color(int iter, const int max_iter);

int get_color_black_white(int iter, const int max_iter);


t_get_color_func get_next_color_func() {
    static t_get_color_func color_funcs[] = {get_color, get_color_black_white};
    static int i = 0;

    return color_funcs[i++ % 2];
}

int get_color(int iter, const int max_iter) {
    if (iter == max_iter)
        return 0x000000;

    return (int) (iter * 255.0 / max_iter) << 16 | (int) (iter * 255.0 / max_iter) << 8 |
           (int) (iter * 255.0 / max_iter);
}

int get_color_black_white(int iter, const int max_iter) {
    if (iter % 2 == 0) {
        return 0x000000;
    } else {
        return 0xFFFFFF;
    }
}