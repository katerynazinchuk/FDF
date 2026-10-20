/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:21:23 by kzinchuk          #+#    #+#             */
/*   Updated: 2024/10/29 16:06:06 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	char_c;
	int				s_length;

	char_c = (unsigned char)c;
	s_length = 0;
	while (s[s_length] != '\0')
	{
		s_length++;
	}
	while (s_length >= 0)
	{
		if (s[s_length] == char_c)
		{
			return ((char *)(s + s_length));
		}
		s_length--;
	}
	return (0);
}
