/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:36:58 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/01/20 15:33:06 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_node *add_node(char *line)
{
    t_node *new_node = malloc(sizeof(t_node));
    if(!new_node)
        return (NULL);
    new_node->line = line;
    new_node->next = NULL;
    return (new_node);
}

t_node *create_list(t_node **head, char *line)
{
    t_node *new_node = add_node(line);
    if (!new_node)
        return (NULL);

    if (!*head)
    {
        *head = new_node;
    }
    else
    {
        t_node *current = *head;
        while (current->next)
            current = current->next;
        current->next = new_node;
    }
    return (new_node);
}

void free_list(t_node *head)
{
    t_node *current = head;
    t_node *next;

    while (current)
    {
        next = current->next;
        free(current->line);
        free(current);
        current = next;
    }
}

t_node *parse_fdf_map(const char *filename)
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
        if (!create_list(&head, line))
        {
            free_list(head);
            close(fd);
            return (NULL);
        }
    }
    close(fd);
    return (head);
}

size_t count_strings(const char *s, char delimiter)
{
    size_t count = 0;
    int in_word = 0;
    while (*s)
    {
        if (*s != delimiter)
        {
            if (!in_word)
            {
                count++;
                in_word = 1;
            }
        }
        else
        {
            in_word = 0;
        }
        s++;
    }
    return count;
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

static int parse_line_to_points(const char *line, t_point *points, size_t y, size_t width)
{
    char **values = ft_split(line, ' ');
    if (!values)
        return (0);

    size_t i = 0;
    while (i < width)
    {
        points[i].x = (float)i;
        points[i].y = (float)y;
        points[i].z = atof(values[i]);

        char *color_ptr = ft_strchr(values[i], ',');
        if (color_ptr)
            points[i].color = strtol(color_ptr + 1, NULL, 16);
        else
            points[i].color = 0xFFFFFF; // Default color

        free(values[i]);
        i++;
    }
    free(values);
    return (1);
}

static t_point **allocate_2d_array(size_t height, size_t width)
{
    t_point **array = malloc(height * sizeof(t_point *));
    if (!array)
    {
        perror("Failed to allocate memory for 2D array");
        return NULL;
    }
    size_t i = 0;
    while (i < height)
    {
        array[i] = malloc(width * sizeof(t_point));
        if (!array[i])
        {
            perror("Failed to allocate memory for row in 2D array");
            size_t j = 0;
            while (j < i)
            {
                free(array[j]);
                j++;
            }
            free(array);
            return NULL;
        }
        i++;
    }
    return array;
}
t_map *initialize_map(t_node *map_lines)
{
    t_map *map = malloc(sizeof(t_map));
    if (!map)
    {
        perror("Failed to allocate memory for t_map");
        return NULL;
    }
    map->height = 0;
    map->width = count_strings(map_lines->line, ' ');
    map->z_min = INT32_MAX;
    map->z_max = INT32_MIN;
    t_node *current = map_lines;
    while (current)
    {
        map->height++;
        current = current->next;
    }
    map->points = allocate_2d_array(map->height, map->width);
    if (!map->points)
    {
        free(map);
        return NULL;
    }
    return map;
}

t_map *populate_map(t_map *map, t_node *map_lines)
{
    t_node *current = map_lines;
    size_t y = 0;
    while (y < (size_t)map->height)
    {
        if (!parse_line_to_points(current->line, map->points[y], y, map->width))
        {
            size_t i = 0;
            while (i < y)
            {
                free(map->points[i]);
                i++;
            }
            free(map->points);
            free(map);
            return NULL;
        }
        size_t x = 0;
        while (x < (size_t)map->width)
        {
            if (map->points[y][x].z < map->z_min)
                map->z_min = (int32_t)map->points[y][x].z;
            if (map->points[y][x].z > map->z_max)
                map->z_max = (int32_t)map->points[y][x].z;
            x++;
        }
        current = current->next;
        y++;
    }

    map->color_range = map->z_max - map->z_min;
    return map;
}
t_map *convert_to_map(t_node *map_lines)
{
    t_map *map = initialize_map(map_lines);
    if (!map)
        return NULL;

    return populate_map(map, map_lines);
}
