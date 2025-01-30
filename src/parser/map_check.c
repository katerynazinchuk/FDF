/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:12:28 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/01/30 14:18:54 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_node	*read_fdf_map(const char *filename)
{
	int		fd;
	t_node	*head;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Failed to open file");
		return (NULL);
	}
	head = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (!list_append(&head, line))
		{
			free_list(head);
			close(fd);
			return (NULL);
		}
		line ++;
		line = get_next_line(fd);
	}
	close(fd);
	return (head);
}

int	validate_map(t_node *map_lines, char delimiter)
{
	size_t	expected_count;
	t_node	*current;

	if (!map_lines)
		return (0);
	expected_count = count_strings(map_lines->line, delimiter);
	current = map_lines->next;
	while (current)
	{
		if (count_strings(current->line, delimiter) != expected_count)
		{
			fprintf(stderr, "Error: Inconsistent number of elem in lines.\n");
			return (0);
		}
		current = current->next;
	}
	return (1);
}
