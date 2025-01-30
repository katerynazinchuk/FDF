/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:22:51 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/01/28 19:30:52 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_error(t_fdf *fdf, t_node *map_lines, t_map *map)
{
	size_t	y;

	if (fdf)
	{
		if (fdf->img)
			mlx_delete_image(fdf->win, fdf->img);
		if (fdf->win)
			mlx_terminate(fdf->win);
		free(fdf);
	}
	if (map_lines)
		free_list(map_lines);
	if (map)
	{
		y = 0;
		while (y < (size_t)map->height)
		{
			free(map->points[y]);
			y++;
		}
		free(map->points);
		free(map);
	}
}

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

int32_t	main(int argc, char **argv)
{
	if (argc != 2)
	{
		write(2, "Usage: ./fdf <map.fdf>\n", 23);
		return (1);
	}
	t_node *map_lines = read_fdf_map(argv[1]);
	if (!map_lines)
		return (EXIT_FAILURE);
	if (!validate_map(map_lines, ' '))
	{
		handle_error(NULL, map_lines, NULL);
		return (EXIT_FAILURE);
	}
	t_map *map = convert_to_map(map_lines);
	if (!map)
	{
		handle_error(NULL, map_lines, NULL);
		return (EXIT_FAILURE);
	}
	t_fdf *fdf = initialize_fdf(map, map_lines);
	if (!fdf)
		return EXIT_FAILURE;
	if (mlx_image_to_window(fdf->win, fdf->img, 0, 0) < 0)
	{
		error();
		handle_error(fdf, map_lines, map);
		return EXIT_FAILURE;
	}
	calculate_offsets(fdf);
	//rotation (and zoom in isometri formula)
	render_top_view(fdf);
	mlx_key_hook(fdf->win, handle_key, fdf);
	mlx_close_hook(fdf->win, handle_close, fdf);
	mlx_loop(fdf->win);
	handle_error(fdf, map_lines, map);
	return (EXIT_SUCCESS);
}
