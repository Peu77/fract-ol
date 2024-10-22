/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:41:55 by eebert            #+#    #+#             */
/*   Updated: 2024/10/14 15:46:38 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "print_pointer.h"
#include <stdbool.h>

static size_t	get_hex_len(unsigned long number)
{
	size_t	len;

	len = 0;
	while (1)
	{
		number /= 16;
		len++;
		if (number == 0)
			break ;
	}
	return (len);
}

static void	itoa_recursive_hex(char *str, unsigned long nbr, size_t start,
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

static void	calculate_len(unsigned long nbr, t_flags *flags, t_nbr_len *nbr_len)
{
	size_t			len;
	const size_t	raw_nbr_len = get_hex_len(nbr);
	size_t			len_with_zeros;

	len_with_zeros = 0;
	len = raw_nbr_len + 2;
	if (flags->plus || flags->space)
	{
		len++;
		nbr_len->has_sign = true;
	}
	else
		nbr_len->has_sign = false;
	if (flags->dot)
		len_with_zeros = len + max(flags->precision - raw_nbr_len, 0);
	else if (flags->zero && flags->width > len && !flags->minus)
		len_with_zeros = max(flags->width, len);
	nbr_len->zero_count = max(len_with_zeros - len, 0);
	nbr_len->len = max(len, len_with_zeros);
	nbr_len->raw_nbr_len = raw_nbr_len;
}

void	print_pointer(t_flags *flags, va_list *args, t_print_result *result)
{
	const unsigned long	number = va_arg(*args, unsigned long);
	t_nbr_len			nbr_len;
	size_t				i;
	char				*buffer;

	calculate_len(number, flags, &nbr_len);
	buffer = ft_calloc(nbr_len.len + 1, sizeof(char));
	if (!buffer)
		return ;
	i = 0;
	if (flags->plus)
		buffer[i++] = '+';
	else if (flags->space)
		buffer[i++] = ' ';
	buffer[i++] = '0';
	buffer[i++] = 'x';
	ft_memset(buffer + i, '0', nbr_len.zero_count);
	itoa_recursive_hex(buffer, number, nbr_len.len - 1, nbr_len.zero_count + i);
	result->str = buffer;
	result->len = ft_strlen(buffer);
}
