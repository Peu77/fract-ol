/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:41:47 by eebert            #+#    #+#             */
/*   Updated: 2024/10/14 16:33:26 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "print_int.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int	handle_special_case(t_flags *flags, t_nbr_len *nbr_len, int ignore_sign)
{
	if ((flags->plus || flags->space) && !ignore_sign)
	{
		nbr_len->len = 1;
		nbr_len->raw_nbr_len = 0;
		nbr_len->zero_count = 0;
		nbr_len->has_sign = true;
		return (1);
	}
	return (0);
}

static void	calculate_len(long nbr, t_flags *flags, t_nbr_len *nbr_len,
		bool ignore_sign)
{
	size_t	len;
	size_t	raw_nbr_len;
	size_t	len_with_zeros;

	raw_nbr_len = ft_numlen_long(nbr);
	len_with_zeros = 0;
	len = raw_nbr_len;
	if (flags->dot && flags->precision == 0 && nbr == 0)
	{
		if (handle_special_case(flags, nbr_len, ignore_sign))
			return ;
		nbr_len->len = 0;
		return ;
	}
	nbr_len->has_sign = ((flags->plus || flags->space || nbr < 0)
			&& !ignore_sign);
	len += nbr_len->has_sign;
	if (flags->dot)
		len_with_zeros = len + max(flags->precision - raw_nbr_len, 0);
	else if (flags->zero && flags->width > len && !flags->minus)
		len_with_zeros = max(flags->width, len);
	nbr_len->zero_count = max(len_with_zeros - len, 0);
	nbr_len->len = max(len, len_with_zeros);
	nbr_len->raw_nbr_len = raw_nbr_len;
}

void	add_sign(char *buffer, long nbr, t_flags *flags)
{
	if (nbr < 0)
		*buffer = '-';
	else if (flags->plus)
		*buffer = '+';
	else if (flags->space)
		*buffer = ' ';
}

void	print_int(t_flags *flags, va_list *args, t_print_result *result)
{
	const int	number = va_arg(*args, int);
	t_nbr_len	nbr_len;
	char		*buffer;

	calculate_len(number, flags, &nbr_len, false);
	if (nbr_len.len == 0)
		return ;
	buffer = ft_calloc(nbr_len.len + 1, sizeof(char));
	if (!buffer)
		return ;
	add_sign(buffer, number, flags);
	ft_memset(buffer + nbr_len.has_sign, '0', nbr_len.zero_count);
	if (nbr_len.raw_nbr_len != 0)
		itoa_recursive_long(buffer, number, nbr_len.len - 1, nbr_len.has_sign
			+ nbr_len.zero_count);
	result->str = buffer;
	result->len = ft_strlen(buffer);
}

void	print_unsigned(t_flags *flags, va_list *args, t_print_result *result)
{
	const unsigned int	number = va_arg(*args, unsigned int);
	t_nbr_len			nbr_len;
	char				*buffer;

	calculate_len(number, flags, &nbr_len, true);
	if (nbr_len.len == 0)
		return ;
	buffer = ft_calloc(nbr_len.len + 1, sizeof(char));
	if (!buffer)
		return ;
	add_sign(buffer, number, flags);
	ft_memset(buffer, '0', nbr_len.zero_count);
	if (nbr_len.raw_nbr_len != 0)
		itoa_recursive_long(buffer, number, nbr_len.len - 1,
			nbr_len.zero_count);
	result->str = buffer;
	result->len = ft_strlen(buffer);
}
