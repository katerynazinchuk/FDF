/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:58:07 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/03/12 16:55:37 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_render_point	project_isometric(t_point point, float angle, t_fdf *fdf)
{
	t_render_point	res;

	res.x = (int)((point.x - point.y) * cos(angle)) + fdf->offset_x;
	res.y = (int)((point.x + point.y) * sin(angle) - point.z) + fdf->offset_y;
	res.z = point.z;
	res.color = point.color;
	return (res);
}

static void	draw_horizontal_lines(t_fdf *fdf, float angle)
{
	int				x;
	int				y;
	t_render_point	start;
	t_render_point	end;

	y = 0;
	while (y < fdf->map->height)
	{
		x = 0;
		while (x + 1 < fdf->map->width)
		{
			start = project_isometric(fdf->map->points[y][x], angle, fdf);
			end = project_isometric(fdf->map->points[y][x + 1], angle, fdf);
			bresenham(fdf, start, end);
			x++;
		}
		y++;
	}
}

static void	draw_vertical_lines(t_fdf *fdf, float angle)
{
	int				x;
	int				y;
	t_render_point	start;
	t_render_point	end;

	x = 0;
	while (x < fdf->map->width)
	{
		y = 0;
		while (y + 1 < fdf->map->height)
		{
			start = project_isometric(fdf->map->points[y][x], angle, fdf);
			end = project_isometric(fdf->map->points[y + 1][x], angle, fdf);
			bresenham(fdf, start, end);
			y++;
		}
		x++;
	}
}

void	render_top_view(t_fdf *fdf)
{
	float	angle;

	angle = 0.6;
	draw_horizontal_lines(fdf, angle);
	draw_vertical_lines(fdf, angle);
}

t_line	new_line(t_render_point start, t_render_point end)
{
	t_line	line;

	line.dx = ft_abs(end.x - start.x);
	line.dy = ft_abs(end.y - start.y);
	if (start.x < end.x)
		line.sx = 1;
	else
		line.sx = -1;
	if (start.y < end.y)
		line.sy = 1;
	else
		line.sy = -1;
	line.err = line.dx - line.dy;
	return (line);
}
