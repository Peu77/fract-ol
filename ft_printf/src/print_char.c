/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:42:10 by eebert            #+#    #+#             */
/*   Updated: 2024/10/14 15:06:55 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

void	print_char(t_flags *flags, va_list *args, t_print_result *result)
{
	const char	c = va_arg(*args, int);

	(void)flags;
	result->str = (ft_strdup(&c));
	result->len = 1;
}
