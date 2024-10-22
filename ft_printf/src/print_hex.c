/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:42:08 by eebert            #+#    #+#             */
/*   Updated: 2024/10/14 15:23:25 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "print_hex.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static size_t	get_hex_len(unsigned int nbr)
{
	size_t	len;

	len = 0;
	while (1)
	{
		nbr /= 16;
		len++;
		if (nbr == 0)
			break ;
	}
	return (len);
}

static void	itoa_recursive_hex(char *str, unsigned int nbr, size_t start,
		size_t stop)
{
	const char	*hex = "0123456789abcdef";

	if (start == stop - 1)
	{
		return ;
	}
	itoa_recursive_hex(str, nbr / 16, start - 1, stop);
	str[start] = hex[nbr % 16];
}

static void	calculate_len(unsigned int nbr, t_flags *flags, t_nbr_len *nbr_len)
{
	size_t			len;
	const size_t	raw_nbr_len = get_hex_len(nbr);
	size_t			len_with_zeros;

	len_with_zeros = 0;
	len = raw_nbr_len;
	if (flags->dot && flags->precision == 0 && nbr == 0)
	{
		nbr_len->len = 0;
		return ;
	}
	if (flags->hashtag && nbr != 0)
	{
		len += 2;
		nbr_len->has_prefix = true;
	}
	else
		nbr_len->has_prefix = false;
	if (flags->dot)
		len_with_zeros = len + max(flags->precision - raw_nbr_len, 0);
	else if (flags->zero && flags->width > len && !flags->minus)
		len_with_zeros = max(flags->width, len);
	nbr_len->zero_count = max(len_with_zeros - len, 0);
	nbr_len->len = max(len, len_with_zeros);
	nbr_len->raw_nbr_len = raw_nbr_len;
}

void	print_hex(t_flags *flags, va_list *args, t_print_result *result)
{
	const unsigned int	number = va_arg(*args, unsigned int);
	t_nbr_len			nbr_len;
	char				*buffer;

	calculate_len(number, flags, &nbr_len);
	if (nbr_len.len == 0)
		return ;
	buffer = ft_calloc(nbr_len.len + 1, sizeof(char));
	if (!buffer)
		return ;
	if (nbr_len.has_prefix)
	{
		buffer[0] = '0';
		buffer[1] = 'x';
	}
	ft_memset(buffer + nbr_len.has_prefix * 2, '0', nbr_len.zero_count);
	itoa_recursive_hex(buffer, number, nbr_len.len - 1, nbr_len.has_prefix * 2
		+ nbr_len.zero_count);
	result->str = buffer;
	result->len = ft_strlen(buffer);
}

void	print_hex_upper(t_flags *flags, va_list *args, t_print_result *result)
{
	const unsigned int	number = va_arg(*args, unsigned int);
	t_nbr_len			nbr_len;
	char				*buffer;

	calculate_len(number, flags, &nbr_len);
	if (nbr_len.len == 0)
		return ;
	buffer = ft_calloc(nbr_len.len + 1, sizeof(char));
	if (!buffer)
		return ;
	if (nbr_len.has_prefix)
	{
		buffer[0] = '0';
		buffer[1] = 'x';
	}
	ft_memset(buffer + nbr_len.has_prefix * 2, '0', nbr_len.zero_count);
	itoa_recursive_hex(buffer, number, nbr_len.len - 1, nbr_len.has_prefix * 2
		+ nbr_len.zero_count);
	while (nbr_len.len > 0 && buffer[--nbr_len.len])
	{
		if (buffer[nbr_len.len] >= 'a' && buffer[nbr_len.len] <= 'z')
			buffer[nbr_len.len] -= 32;
	}
	result->str = buffer;
	result->len = ft_strlen(buffer);
}
