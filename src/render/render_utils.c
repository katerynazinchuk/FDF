/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:08:55 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/03/12 16:46:24 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static void	set_default_height(t_fdf *fdf, float span)
{
	float	z_range;

	z_range = fdf->map->z_max - fdf->map->z_min;
	if (z_range <= 0)
		return ;
	fdf->z_scale = 0.15 * span / z_range;
	if (fdf->z_scale > 1)
		fdf->z_scale = 1;
}

void	calculate_offsets(t_fdf *fdf)
{
	float	span;
	float	zoom_x;
	float	zoom_y;
	int		diff;

	span = (fdf->map->width - 1) + (fdf->map->height - 1);
	if (span < 1)
		span = 1;
	zoom_x = WIDTH * 0.8 / (span * cos(ANGLE));
	zoom_y = HEIGHT * 0.6 / (span * sin(ANGLE));
	fdf->zoom = fminf(zoom_x, zoom_y);
	diff = (fdf->map->width - 1) - (fdf->map->height - 1);
	fdf->offset_x = WIDTH / 2 - diff * cos(ANGLE) * fdf->zoom / 2;
	fdf->offset_y = (HEIGHT - span * sin(ANGLE) * fdf->zoom) / 2 + HEIGHT / 10;
	set_default_height(fdf, span);
}
