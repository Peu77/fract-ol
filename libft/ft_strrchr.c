/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:05:24 by eebert            #+#    #+#             */
/*   Updated: 2024/09/25 15:05:24 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*last;

	last = NULL;
	while (*str)
	{
		if (*str == (unsigned char)c)
		{
			last = (char *)str;
		}
		str++;
	}
	if (c == 0)
	{
		return ((char *)str);
	}
	return (last);
}
