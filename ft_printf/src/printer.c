/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:50:34 by eebert            #+#    #+#             */
/*   Updated: 2024/10/14 15:32:22 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printer	*get_printer(char type)
{
	static t_printer	printers[] = {{'d', &print_int}, {'i', &print_int},
	{'u', &print_unsigned}, {'x', &print_hex}, {'X', &print_hex_upper},
	{'c', &print_char}, {'s', &print_string}, {'p', &print_pointer},
	{'%', &print_percent}, {0, 0}};
	int					i;

	i = 0;
	while (printers[i].type)
	{
		if (printers[i].type == type)
			return (&printers[i]);
		i++;
	}
	return (NULL);
}
