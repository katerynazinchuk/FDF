/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:36:58 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/01/24 19:13:09 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int parse_line_to_points(const char *line, t_point *points, size_t y, size_t width)
{
    char **values = ft_split(line, ' ');
    if (!values)
        return (0);
    size_t i = 0;
    while (i < width)
    {
        char *comma_ptr = ft_strchr(values[i], ',');
        if(comma_ptr)
        {
            *comma_ptr = '\0';
            points[i].z = (float)ft_atoi(values[i]);
            points[i].color = hex_to_int(comma_ptr + 1) * 256 + 0xFF;
        }
        else
        {
            points[i].z = (float)ft_atoi(values[i]);
            points[i].color = 0xFFFFFFFF;
        }
        points[i].x = (float)i * GRIDSPASE;
        points[i].y = (float)y * GRIDSPASE;
        // printf("points[i].z = %f\n", points[i].z);
        // printf("points[i].x = %f\n", points[i].x);
        // printf("points[i].y = %f\n", points[i].y);
        // printf("points[i].color = %d\n", points[i].color);
        free(values[i]);
        i++;
    }
    free(values);
    return (1);
}

static t_point **allocate_map(size_t height, size_t width)
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
    map->points = allocate_map(map->height, map->width);
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
