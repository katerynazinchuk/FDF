/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:22:51 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/03/11 18:17:14 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*process_map(const char *filename)
{
	t_node	*map_lines;
	t_map	*map;

	map_lines = read_fdf_map(filename);
	if (!map_lines)
		return (NULL);
	if (!validate_map(map_lines, ' '))
	{
		free_list(map_lines);
		return (NULL);
	}
	map = convert_to_map(map_lines);
	if (!map)
	{
		free_list(map_lines);
		return (NULL);
	}
	return (map);
}

t_fdf	*initialize_fdf(t_map *map, t_node *map_lines)
{
	t_fdf	*fdf;

	fdf = malloc(sizeof(t_fdf));
	if (!fdf)
	{
		handle_error(NULL, map_lines, map);
		return (NULL);
	}
	fdf->offset_x = 0;
	fdf->offset_y = 0;
	fdf->map = map;
	fdf->win = mlx_init(WIDTH, HEIGHT, "fdf", true);
	if (!fdf->win)
	{
		handle_error(fdf, map_lines, map);
		return (NULL);
	}
	fdf->img = mlx_new_image(fdf->win, WIDTH, HEIGHT);
	if (!fdf->img)
	{
		handle_error(fdf, map_lines, map);
		return (NULL);
	}
	return (fdf);
}
