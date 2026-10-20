/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:20:48 by kzinchuk          #+#    #+#             */
/*   Updated: 2024/10/29 15:34:26 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	count_strings(const char *s, char delimiter);
static char		**allocate_split(const char *s, char c);
static int		populate_split(char **result, const char *s, char c);
static void		free_split(char **result);

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = allocate_split(s, c);
	if (!result)
		return (NULL);
	if (!populate_split(result, s, c))
		return (NULL);
	return (result);
}

static size_t	count_strings(const char *s, char delimiter)
{
	size_t	count;
	int		word;

	word = 0;
	count = 0;
	while (*s)
	{
		if (*s != delimiter)
		{
			if (!word)
			{
				count ++;
				word = 1;
			}
		}
		else
		{
			word = 0;
		}
		s++;
	}
	return (count);
}

static char	**allocate_split(const char *s, char c)
{
	size_t	count;
	char	**result;

	count = count_strings(s, c);
	result = (char **)malloc((count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result[count] = NULL;
	return (result);
}

static int	populate_split(char **result, const char *s, char c)
{
	size_t	i;
	size_t	index;
	size_t	start;

	i = 0;
	index = 0;
	while (index < count_strings(s, c))
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > start)
		{
			result[index] = ft_substr(s, start, i - start);
			if (!result[index])
			{
				free_split(result);
				return (0);
			}
			index++;
		}
	}
	return (1);
}

static void	free_split(char **result)
{
	size_t	i;

	if (result)
	{
		i = 0;
		while (result[i] != NULL)
		{
			free(result[i]);
			i++;
		}
		free(result);
	}
}
