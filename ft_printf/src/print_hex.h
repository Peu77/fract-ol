/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:08:28 by eebert            #+#    #+#             */
/*   Updated: 2024/10/11 14:22:42 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_HEX_H
# define PRINT_HEX_H

# include <stdbool.h>
# include <unistd.h>

typedef struct s_nbr_len
{
	size_t	len;
	size_t	raw_nbr_len;
	size_t	zero_count;
	bool	has_prefix;
}			t_nbr_len;

#endif