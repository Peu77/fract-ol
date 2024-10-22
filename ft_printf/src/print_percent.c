/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_percent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:41:52 by eebert            #+#    #+#             */
/*   Updated: 2024/10/14 15:08:57 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

void	print_percent(t_flags *flags, va_list *args, t_print_result *result)
{
	(void)flags;
	(void)args;
	result->str = ft_strdup("%");
	result->len = 1;
}
