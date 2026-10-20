/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:20:59 by kzinchuk          #+#    #+#             */
/*   Updated: 2024/10/29 15:35:01 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_string;
	size_t	len1;
	size_t	len2;
	size_t	full_len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	full_len = len1 + len2 + 1;
	new_string = malloc(full_len);
	if (!new_string)
	{
		return (NULL);
	}
	ft_strlcpy(new_string, s1, len1 + 1);
	ft_strlcpy(new_string + len1, s2, len2 + 1);
	return (new_string);
}
