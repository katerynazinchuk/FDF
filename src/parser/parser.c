/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:36:58 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/01/28 18:53:02 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	parse_line_to_p(const char *line, t_point *points, size_t y, size_t width)
{
	char	**values;
	size_t	i;
	char	*comma_ptr;

	values = ft_split(line, ' ');
	if (!values)
		return (0);
	i = 0;
	while (i < width)
	{
		comma_ptr = ft_strchr(values[i], ',');
		if (comma_ptr)
		{
			*comma_ptr = '\0';
			points[i].z = (float)ft_atoi(values[i]);// * GRIDSPASE / 2;
			points[i].color = hex_to_int(comma_ptr + 1) * 256 + 0xFF;
		}
		else
		{
			points[i].z = (float)ft_atoi(values[i]);// * GRIDSPASE / 2;
			points[i].color = 0xFFFFFFFF;
		}
		points[i].x = (float)i * GRIDSPASE;
		points[i].y = (float)y * GRIDSPASE;
		free(values[i]);
		i++;
	}
	free(values);
	return (1);
}

static t_point	**allocate_map(size_t height, size_t width)
{
	t_point	**array;
	size_t	i;
	size_t	j;

	array = malloc(height * sizeof(t_point *));
	if (!array)
	{
		perror("Failed to allocate memory for 2D array");
		return (NULL);
	}
	i = -1;
	while (++i < height)
	{
		array[i] = malloc(width * sizeof(t_point));
		if (!array[i])
		{
			perror("Failed to allocate memory for row in 2D array");
			j = -1;
			while (++j < i)
				free(array[j]);
			free(array);
			return (NULL);
		}
	}
	return (array);
}

t_map	*initialize_map(t_node *map_lines)
{
	t_map	*map;
	t_node	*current;

	map = malloc(sizeof(t_map));
	if (!map)
	{
		perror("Failed to allocate memory for t_map");
		return (NULL);
	}
	map->height = 0;
	map->width = count_strings(map_lines->line, ' ');
	map->z_min = INT32_MAX;
	map->z_max = INT32_MIN;
	current = map_lines;
	while (current)
	{
		map->height++;
		current = current->next;
	}
	map->points = allocate_map(map->height, map->width);
	if (!map->points)
		return (free(map), NULL);
	return (map);
}

t_map	*populate_map(t_map *map, t_node *map_lines)
{
	t_node	*current;
	size_t	y;
	size_t	i;
	size_t	x;

	current = map_lines;
	y = 0;
	while (y < (size_t)map->height)
	{
		if (!parse_line_to_p(current->line, map->points[y], y, map->width))
		{
			i = -1;
			while (++i < y)
				free(map->points[i]);
			free(map->points);
			free(map);
			return (NULL);
		}
		x = -1;
		while (++x < (size_t)map->width)
		{
			if (map->points[y][x].z < map->z_min)
				map->z_min = (int32_t)map->points[y][x].z;
			if (map->points[y][x].z > map->z_max)
				map->z_max = (int32_t)map->points[y][x].z;
		}
		current = current->next;
		y++;
	}
	map->color_range = map->z_max - map->z_min;
	return (map);
}

t_map	*convert_to_map(t_node *map_lines)
{
	t_map	*map;

	map = initialize_map(map_lines);
	if (!map)
		return (NULL);
	return (populate_map(map, map_lines));
}
