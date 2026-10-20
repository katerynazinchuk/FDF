/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:55:00 by kzinchuk          #+#    #+#             */
/*   Updated: 2024/10/30 12:50:20 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = (char *)s;
	while (i < n)
		ptr[i++] = '\0';
}
// # include <stdlib.h>
// # include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	buffer[10] = "abcdefghi";
//     char	buffer2[10] = "abcdefghi";

// 	ft_bzero(buffer, 100);
//     bzero(buffer2, 111);
// 	printf("%s\n", buffer);
// 	return (0);
// }