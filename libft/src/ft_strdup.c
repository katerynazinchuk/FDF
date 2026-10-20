/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:20:55 by kzinchuk          #+#    #+#             */
/*   Updated: 2024/10/29 15:34:40 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*dup ;

	dup = (char *)malloc(ft_strlen(s) + 1);
	if (!dup)
	{
		return (NULL);
	}
	ft_strlcpy(dup, s, ft_strlen(s) + 1);
	return (dup);
}
