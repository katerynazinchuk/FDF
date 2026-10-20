/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:21:30 by kzinchuk          #+#    #+#             */
/*   Updated: 2024/10/29 15:36:43 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_string;

	if (!s)
	{
		return (NULL);
	}
	if (start >= ft_strlen(s))
	{
		return (ft_strdup(""));
	}
	if (start < ft_strlen(s))
	{
		if (len > ft_strlen(s) - start)
		{
			len = ft_strlen(s) - start;
		}
	}
	new_string = malloc(sizeof(char) * (len + 1));
	if (!new_string)
	{
		return (NULL);
	}
	ft_strlcpy(new_string, s + start, len + 1);
	return (new_string);
}
