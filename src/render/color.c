/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:09:43 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/03/12 16:40:34 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_color	extract_color(uint32_t color)
{
	t_color	result;

	result.r = (color >> 16) & 0xFF;
	result.g = (color >> 8) & 0xFF;
	result.b = color & 0xFF;
	result.a = (color >> 24) & 0xFF;
	return (result);
}

uint32_t	combine_color(t_color result)
{
	return (result.a << 24 | result.r << 16 | result.g << 8 | result.b);
}

uint32_t	interpolate_color(uint32_t start_color, uint32_t end_color, float t)
{
	t_color	color_start;
	t_color	color_end;
	t_color	result;

	color_start = extract_color(start_color);
	color_end = extract_color(end_color);
	result.r = color_start.r + (color_end.r - color_start.r) * t;
	result.g = color_start.g + (color_end.g - color_start.g) * t;
	result.b = color_start.b + (color_end.b - color_start.b) * t;
	result.a = color_start.a + (color_end.a - color_start.a) * t;
	return (combine_color(result));
}

uint32_t	calculate_gradient_color(t_map *map, int32_t z)
{
	float		t;
	uint32_t	color_start;
	uint32_t	color_end;

	t = (float)(z - map->z_min) / (float)(map->z_max - map->z_min);
	color_start = 0xFFFFFFFF;
	color_end = 0xFFFF00FF;
	if (t < 0)
		t = 0;
	if (t > 1)
		t = 1;
	return (interpolate_color(color_start, color_end, t));
}
// Interpolate color based on normalized z before return
// in calculate_gradient_color