/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:15:18 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/03/12 16:55:56 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	put_pixel_bresenham(t_fdf *fdf, t_bresenham *b, uint32_t color)
{
	if (b->start.x >= 0 && b->start.x < (int)fdf->img->width && \
		b->start.y >= 0 && b->start.y < (int)fdf->img->height)
		mlx_put_pixel(fdf->img, b->start.x, b->start.y, color);
}

static void	update_bresenham_position(t_bresenham *b)
{
	int	double_error;

	double_error = 2 * b->line.err;
	if (double_error > -b->line.dy)
	{
		b->line.err -= b->line.dy;
		b->start.x += b->line.sx;
	}
	if (double_error < b->line.dx)
	{
		b->line.err += b->line.dx;
		b->start.y += b->line.sy;
	}
}

static void	bresenham_loop(t_fdf *fdf, t_bresenham *b)
{
	float		t;
	uint32_t	color;

	while (1)
	{
		t = 0.0f;
		if (b->total_steps != 0)
			t = (float)b->current_step / b->total_steps;
		color = interpolate_color(b->color_start, b->color_end, t);
		put_pixel_bresenham(fdf, b, color);
		if (b->start.x == b->end.x && b->start.y == b->end.y)
			break ;
		update_bresenham_position(b);
		b->current_step++;
	}
}

static void	initialize_bresenham(t_bresenham *b, t_fdf *fdf, \
						t_render_point start, t_render_point end)
{
	b->line = new_line(start, end);
	b->start = start;
	b->end = end;
	b->current_step = 0;
	if (start.color != 0)
		b->color_start = start.color;
	else
		b->color_start = calculate_gradient_color(fdf->map, start.z);
	if (end.color != 0)
		b->color_end = end.color;
	else
		b->color_end = calculate_gradient_color(fdf->map, end.z);
	if (b->line.dx > b->line.dy)
		b->total_steps = b->line.dx;
	else
		b->total_steps = b->line.dy;
}

void	bresenham(t_fdf *fdf, t_render_point start, t_render_point end)
{
	t_bresenham	b;

	initialize_bresenham(&b, fdf, start, end);
	bresenham_loop(fdf, &b);
}
