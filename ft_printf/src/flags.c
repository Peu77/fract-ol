/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:17:17 by eebert            #+#    #+#             */
/*   Updated: 2024/10/11 14:22:22 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int	parse_number(const char *format, int *i, va_list *args)
{
	int	number;

	if (format[*i] == '*')
	{
		(*i)++;
		return (va_arg(*args, int));
	}
	number = 0;
	while (ft_isdigit(format[*i]))
	{
		number = number * 10 + format[*i] - '0';
		(*i)++;
	}
	return (number);
}

static int	is_flag(const char c)
{
	return (c == '#' || c == '0' || c == '-' || c == ' ' || c == '+');
}

static void	parse_precision(const char *format, t_flags *flags, int *i,
		va_list *args)
{
	int	precision_number;

	if (format[*i] == '.')
	{
		flags->dot = 1;
		(*i)++;
		precision_number = parse_number(format, i, args);
		if (precision_number < 0)
		{
			flags->dot = 0;
			flags->precision = 0;
		}
		else
			flags->precision = precision_number;
	}
}

void	parse_width(const char *format, t_flags *flags, int *i, va_list *args)
{
	int	width;

	width = parse_number(format, i, args);
	if (width < 0)
	{
		flags->minus = 1;
		flags->width = -width;
	}
	else
		flags->width = width;
}

int	parse_flags(const char *format, t_flags *flags, va_list *args)
{
	int	i;

	i = 0;
	while (is_flag(format[i]))
	{
		if (format[i] == '#')
			flags->hashtag = 1;
		if (format[i] == '0')
			flags->zero = 1;
		if (format[i] == '-')
			flags->minus = 1;
		if (format[i] == ' ')
			flags->space = 1;
		if (format[i] == '+')
			flags->plus = 1;
		i++;
	}
	parse_width(format, flags, &i, args);
	parse_precision(format, flags, &i, args);
	return (i);
}
