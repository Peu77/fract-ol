/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:02:40 by eebert            #+#    #+#             */
/*   Updated: 2024/10/14 14:37:57 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(int n)
{
	int	len;

	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	itoa_recursive(char *str, int n, int start)
{
	if (n == 0)
	{
		return ;
	}
	itoa_recursive(str, n / 10, start - 1);
	str[start] = n % 10 + '0';
}

char	*ft_itoa(int n)
{
	int		is_negative;
	char	*str;
	int		num_len;

	if (n == -2147483648)
	{
		return (ft_strdup("-2147483648"));
	}
	if (n == 0)
	{
		return (ft_strdup("0"));
	}
	is_negative = n < 0;
	num_len = ft_numlen(n);
	str = ft_calloc(num_len + is_negative + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (is_negative)
	{
		n = -n;
		str[0] = '-';
	}
	itoa_recursive(str, n, num_len - 1 + is_negative);
	return (str);
}
