/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:22:52 by eebert            #+#    #+#             */
/*   Updated: 2024/10/22 14:23:12 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

float ft_atof(const char *str) {
    float res = 0.0f;
    float sign = 1;
    int i = 0;
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
        i++;
    if (str[i] == '-' || str[i] == '+')
        sign = 1 - 2 * (str[i++] == '-');
    while (str[i] >= '0' && str[i] <= '9')
        res = res * 10 + str[i++] - '0';
    if (str[i] == '.')
        i++;
    float f = 1;
    while (str[i] >= '0' && str[i] <= '9') {
        res = res * 10 + str[i++] - '0';
        f *= 10;
    }
    return sign * res / f;
}