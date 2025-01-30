/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:31:38 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/01/28 19:35:41 by kzinchuk         ###   ########.fr       */
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
