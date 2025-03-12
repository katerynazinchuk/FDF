/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:31:38 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/03/11 18:17:09 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	handle_close(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	mlx_terminate(fdf->win);
	free(fdf);
	exit(EXIT_SUCCESS);
}

void	clear_and_render(t_fdf *fdf)
{
	ft_memset(fdf->img->pixels, 0, \
			fdf->img->width * fdf->img->height * sizeof(uint32_t));
	render_top_view(fdf);
}

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
