/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_controls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:33:38 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/03/11 18:17:16 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_escape(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		handle_close(param);
}

void	handle_transform(mlx_key_data_t keydata, t_fdf *fdf)
{
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		fdf->offset_x -= GRIDSPASE;
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		fdf->offset_x += GRIDSPASE;
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		fdf->offset_y -= GRIDSPASE;
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		fdf->offset_y += GRIDSPASE;
	clear_and_render(fdf);
}

void	handle_key(mlx_key_data_t keydata, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (!fdf || !fdf->map)
		return ;
	handle_escape(keydata, param);
	handle_transform(keydata, fdf);
}
