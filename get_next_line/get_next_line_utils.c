/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:29:56 by kzinchuk          #+#    #+#             */
/*   Updated: 2024/11/29 16:05:50 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	found_newline(t_list *node_list)
{
	int		i;
	t_list	*current;

	if (node_list == NULL)
		return (0);
	current = get_last_in_list(node_list);
	i = 0;
	while (current->content[i])
	{
		if (current->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_list	*get_last_in_list(t_list *node_list)
{
	t_list	*current;

	current = node_list;
	while (current && current->next)
		current = current->next;
	return (current);
}

void	allocate_line(char **line, t_list *node_list)
{
	int	i;
	int	len;

	len = 0;
	while (node_list)
	{
		i = 0;
		while (node_list->content[i])
		{
			if (node_list->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		node_list = node_list->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
	if (*line == NULL)
		return ;
}

void	free_node_list(t_list **node_list)
{
	t_list	*current_node;
	t_list	*next_node;

	if (node_list == NULL || *node_list == NULL)
		return ;
	current_node = *node_list;
	while (current_node)
	{
		free(current_node->content);
		next_node = current_node->next;
		free(current_node);
		current_node = next_node;
	}
	*node_list = NULL;
}

t_list	*create_node(ssize_t content_size)
{
	t_list *const	output = malloc(sizeof(t_list) * 1);

	if (!output)
		return (NULL);
	if (content_size < 0)
		return (free(output), NULL);
	output->next = NULL;
	output->content = malloc(sizeof(char) * content_size);
	if (!output->content)
		return (free(output), NULL);
	return (output);
}
