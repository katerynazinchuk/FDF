/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kat <kat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:15:22 by kzinchuk          #+#    #+#             */
/*   Updated: 2026/10/20 08:04:58 by kat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*node_list = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	read_and_store(fd, &node_list);
	if (node_list == NULL)
		return (NULL);
	extract_line(node_list, &line);
	clean_node_list(&node_list);
	if (line && line[0] != '\0')
		return (line);
	free_node_list(&node_list);
	free(line);
	return (NULL);
}

void	read_and_store(int fd, t_list **node_list)
{
	char	*buf;
	int		buffer_size;

	buffer_size = 1;
	while (!found_newline(*node_list) && buffer_size != 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buf == NULL)
		{
			free_node_list(node_list);
			return ;
		}
		buffer_size = (int)read(fd, buf, BUFFER_SIZE);
		if ((*node_list == NULL && buffer_size == 0) || buffer_size == -1)
		{
			free(buf);
			free_node_list(node_list);
			return ;
		}
		buf[buffer_size] = '\0';
		if (add_to_node_list(node_list, buf, buffer_size) == NULL)
			free_node_list(node_list);
		free(buf);
	}
}

void	*add_to_node_list(t_list **node_list, char *buf, int buffer_size)
{
	int		i;
	t_list	*new_node;
	t_list	*last_node;

	new_node = create_node(buffer_size + 1);
	if (new_node == NULL)
		return (NULL);
	i = 0;
	while (buf[i] && i < buffer_size)
	{
		new_node->content[i] = buf[i];
		i++;
	}
	new_node->content[i] = '\0';
	last_node = get_last_in_list(*node_list);
	if (!last_node)
		*node_list = new_node;
	else
		last_node->next = new_node;
	return (new_node);
}

void	extract_line(t_list *node_list, char **line)
{
	int	i;
	int	j;

	if (node_list == NULL)
		return ;
	allocate_line(line, node_list);
	if (*line == NULL)
		return ;
	j = 0;
	while (node_list)
	{
		i = 0;
		while (node_list->content[i])
		{
			if (node_list->content[i] == '\n')
			{
				(*line)[j++] = node_list->content[i];
				break ;
			}
			(*line)[j++] = node_list->content[i++];
		}
		node_list = node_list->next;
	}
	(*line)[j] = '\0';
}

int	clean_node_list(t_list **node_list)
{
	t_list	*last;
	t_list	*clean_node;
	int		i;
	int		j;

	last = get_last_in_list(*node_list);
	if (!last)
		return (0);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content[i] == '\n')
		i++;
	j = i;
	while (last->content[i])
		i++;
	clean_node = create_node(i - j + 1);
	if (clean_node == NULL)
		return (free_node_list(node_list), 0);
	clean_node->content[i - j] = 0;
	while (--i - j >= 0)// if \n in the end of the line will not go here
		clean_node->content[i - j] = last->content[i];
	free_node_list(node_list);
	*node_list = clean_node;
	return (0);
}