/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:56:30 by eebert            #+#    #+#             */
/*   Updated: 2024/10/11 14:04:53 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// get the length of a number without sign

size_t	ft_numlen_long(long n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		n = -n;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	itoa_recursive_long(char *str, long nbr, size_t start, size_t stop)
{
	if (start == stop - 1)
	{
		return ;
	}
	itoa_recursive_long(str, nbr / 10, start - 1, stop);
	str[start] = ft_abs(nbr % 10) + '0';
}

int	max(int a, int b)
{
	if (a > b)
	{
		return (a);
	}
	return (b);
}
