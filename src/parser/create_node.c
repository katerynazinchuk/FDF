/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:08:58 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/01/28 19:37:30 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_node	*add_node(char *line)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->line = line;
	new_node->next = NULL;
	return (new_node);
}

t_node	*list_append(t_node **head, char *line)
{
	t_node	*new_node;
	t_node	*current;

	new_node = add_node(line);
	if (!new_node)
		return (NULL);
	if (!*head)
	{
		*head = new_node;
	}
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
	return (new_node);
}

void	free_list(t_node *head)
{
	t_node	*current;
	t_node	*next;

	current = head;
	while (current)
	{
		next = current->next;
		free(current->line);
		free(current);
		current = next;
	}
}
