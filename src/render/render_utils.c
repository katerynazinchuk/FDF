/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:08:55 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/01/28 15:25:46 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	calculate_offsets(t_fdf *fdf)
{
	fdf->offset_x = WIDTH / 2;
	fdf->offset_y = HEIGHT / 3;
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
