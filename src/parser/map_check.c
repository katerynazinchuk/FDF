/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:12:28 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/01/24 19:12:53 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_node *read_fdf_map(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("Failed to open file");
        return (NULL);
    }
    t_node *head = NULL;
    char *line;
    while ((line = get_next_line(fd)) != NULL)
    {
        if (!list_append(&head, line))
        {
            free_list(head);
            close(fd);
            return (NULL);
        }
    }
    close(fd);
    return (head);
}

int validate_map(t_node *map_lines, char delimiter)
{
    if (!map_lines)
        return 0;
    size_t expected_count = count_strings(map_lines->line, delimiter);
    t_node *current = map_lines->next;
    while (current)
    {
        if (count_strings(current->line, delimiter) != expected_count)
        {
            fprintf(stderr, "Error: Inconsistent number of elements in the map lines.\n");
            return 0;
        }
        current = current->next;
    }
    return 1;
}