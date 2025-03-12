/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:10:58 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/02/20 18:57:39 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

size_t	count_strings(const char *s, char delimiter)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != delimiter)
		{
			if (!in_word)
			{
				count++;
				in_word = 1;
			}
		}
		else
			in_word = 0;
		s++;
	}
	return (count);
}

int	hex_to_int(const char *hex)
{
	int	result;
	int	value;

	result = 0;
	if (!hex || !*hex)
		return (-1);
	if (hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X'))
		hex += 2;
	while (*hex)
	{
		if (ft_isdigit(*hex))
			value = *hex - '0';
		else if (*hex >= 'A' && *hex <= 'F')
			value = *hex - 'A' + 10;
		else if (*hex >= 'a' && *hex <= 'f')
			value = *hex - 'a' + 10;
		else
			return (-1);
		result = (result * 16) + value;
		hex++;
	}
	return (result);
}
