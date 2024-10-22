/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:41:58 by eebert            #+#    #+#             */
/*   Updated: 2024/10/14 15:43:36 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

void	print_string(t_flags *flags, va_list *args, t_print_result *result)
{
	char	*str;

	str = va_arg(*args, char *);
	if (!str)
		str = "(null)";
	if (flags->dot && flags->precision < ft_strlen(str))
	{
		result->len = flags->precision;
		result->str = ft_substr(str, 0, flags->precision);
		return ;
	}
	result->len = ft_strlen(str);
	result->str = ft_strdup(str);
}
