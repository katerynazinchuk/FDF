/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:36:51 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/03/12 16:45:19 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int32_t	main(int argc, char **argv)
{
	t_node	*map_lines;
	t_map	*map;
	t_fdf	*fdf;

	if (!validate_arguments(argc))
		return (EXIT_FAILURE);
	map = validate_and_store_map(argv[1], &map_lines);
	if (!map)
		return (EXIT_FAILURE);
	fdf = initialize_fdf(map, map_lines);
	if (!fdf)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(fdf->win, fdf->img, 0, 0) < 0)
	{
		error();
		handle_error(fdf, map_lines, map);
		return (EXIT_FAILURE);
	}
	calculate_offsets(fdf);
	render_top_view(fdf);
	start_mlx_loop(fdf);
	handle_error(fdf, map_lines, map);
	return (EXIT_SUCCESS);
}

int	validate_arguments(int argc)
{
	if (argc != 2)
	{
		write(2, "Usage: ./fdf <map.fdf>\n", 23);
		return (0);
	}
	return (1);
}

t_map	*validate_and_store_map(const char *filename, t_node **map_lines)
{
	t_map	*map;

	*map_lines = read_fdf_map(filename);
	if (!map_lines)
		return (NULL);
	if (!validate_map(*map_lines, ' '))
	{
		handle_error(NULL, *map_lines, NULL);
		return (NULL);
	}
	map = convert_to_map(*map_lines);
	if (!map)
		handle_error(NULL, *map_lines, NULL);
	return (map);
}

void	start_mlx_loop(t_fdf *fdf)
{
	mlx_key_hook(fdf->win, handle_key, fdf);
	mlx_close_hook(fdf->win, handle_close, fdf);
	mlx_loop(fdf->win);
}
