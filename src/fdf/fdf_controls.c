/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_controls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:33:38 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/01/24 17:13:31 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void handle_key_input(mlx_key_data_t keydata, void *param)
{
    t_fdf *fdf = (t_fdf *)param;
    if (!fdf || !fdf->map)
        return ;
    if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
        fdf->offset_x -= 10;
    if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
        fdf->offset_x += 10;
    if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
        fdf->offset_y -= 10;
    if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
        fdf->offset_y += 10;
   
    ft_memset(fdf->img->pixels, 0, fdf->img->width * fdf->img->height * sizeof(uint32_t));
    render_top_view(fdf);
}
void handle_close(void *param)
{
    t_fdf *fdf = (t_fdf *)param;
    mlx_terminate(fdf->win);
    free(fdf);
    exit(EXIT_SUCCESS);
}

void handle_escape(mlx_key_data_t keydata, void *param)
{
    t_fdf *fdf = (t_fdf *)param;
    (void)fdf;
        if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        {
            handle_close(param);
        }   
}

void error(void)
{
    fprintf(stderr, "%s", mlx_strerror(mlx_errno));
    exit(EXIT_FAILURE);
}