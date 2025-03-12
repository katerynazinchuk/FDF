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

void	calculate_offsets(t_fdf *fdf)
{
	fdf->offset_x = WIDTH / 2;
	fdf->offset_y = HEIGHT / 3;
}
