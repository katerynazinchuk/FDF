/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:21:27 by kzinchuk          #+#    #+#             */
/*   Updated: 2024/10/29 15:36:37 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new_string;
	size_t	first;
	size_t	last;

	if (!s1)
		return (NULL);
	first = 0;
	last = ft_strlen(s1);
	while (s1[first] && ft_strchr(set, s1[first]))
	{
		first++;
	}
	while (last > first && s1 && ft_strrchr(set, s1[last - 1]))
	{
		last--;
	}
	new_string = (char *)malloc(last - first + 1);
	if (!new_string)
		return (NULL);
	ft_strlcpy(new_string, s1 + first, last - first + 1);
	return (new_string);
}
