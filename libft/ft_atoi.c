/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:56:53 by peu77             #+#    #+#             */
/*   Updated: 2024/09/25 15:00:49 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\r' || c == '\f' || c == '\v' || c == '\n'
		|| c == '\t');
}

int	ft_atoi(const char *str)
{
	int				nb;
	unsigned int	minus_count;

	nb = 0;
	minus_count = 0;
	while (is_space(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus_count++;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nb = *str - '0' + (nb * 10);
		str++;
	}
	if (minus_count % 2 != 0)
		return (-nb);
	return (nb);
}
