/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:58:07 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/01/28 19:16:57 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_render_point	project_isometric(t_point point, float angle, t_fdf *fdf)
{
	t_render_point	result;

	result.x = (int)((point.x - point.y) * cos(angle)) + fdf->offset_x;
	result.y = (int)((point.x + point.y) * sin(angle) - point.z) + fdf->offset_y;
	result.z = point.z;
	result.color = point.color;

	return result;
}

void	bresenham_line(t_fdf *fdf, t_render_point start, t_render_point end)
{
	t_line		line;
	uint32_t	color_start;
	uint32_t	color_end;
	int			total_steps;

	line = new_line(start, end);
	if(start.color != 0)
		color_start = start.color;
	else
		color_start = calculate_gradient_color(fdf->map, start.z);
	if (end.color != 0)
		color_end = end.color;
	else
		color_end = calculate_gradient_color(fdf->map, end.z);
	if (line.dx > line.dy)
		total_steps = line.dx;
	else
		total_steps = line.dy;
	int current_step = 0;
	while (1)
	{
		float t = 0.0f;
		if (total_steps != 0)
			t = (float)current_step / total_steps;

		uint32_t color = interpolate_color(color_start, color_end, t);
		
		if (start.x >= 0 && start.x < (int)fdf->img->width &&
			start.y >= 0 && start.y < (int)fdf->img->height)
			mlx_put_pixel(fdf->img, start.x, start.y, color);
		if (start.x == end.x && start.y == end.y)
			break;
		int e2 = 2 * line.err;
		if (e2 > -line.dy)
		{
			line.err -= line.dy;
			start.x += line.sx;
		}
		if (e2 < line.dx)
		{
			line.err += line.dx;
			start.y += line.sy;
		}
		current_step++;
	}
}

static void draw_horizontal_lines(t_fdf *fdf, float angle)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->map->height)
	{
		x = 0;
		while (x + 1 < fdf->map->width)
		{
			t_render_point start = project_isometric(fdf->map->points[y][x], angle, fdf);
			t_render_point end = project_isometric(fdf->map->points[y][x + 1], angle,  fdf);
			bresenham_line(fdf, start, end);
			x++;
		}
		y++;
	}
}

static void	draw_vertical_lines(t_fdf *fdf, float angle)
{
	int	x;
	int	y;

	x = 0;
	while (x < fdf->map->width)
	{
		y = 0;
		while (y + 1 < fdf->map->height)
		{
			t_render_point start = project_isometric(fdf->map->points[y][x], angle, fdf);
			t_render_point end = project_isometric(fdf->map->points[y + 1][x], angle, fdf);
			bresenham_line(fdf, start, end);
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
