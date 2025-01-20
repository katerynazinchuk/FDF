// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   fdf.c                                              :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/12/18 18:22:51 by kzinchuk          #+#    #+#             */
// /*   Updated: 2025/01/18 17:22:32 by kzinchuk         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// //      - get heigh (lines of text)
// //      - get width (how many nubers in line)
// //      - allocate memory for **int by using width and height
// //      - read file and write number into matrix by using split and atoi

// //2. drawing line function
// //      -find by how we eed to increase  x and y 
#include "fdf.h"

void handle_close(void *param)
{
    t_fdf *fdf = (t_fdf *)param;

    mlx_terminate(fdf->win);
    free(fdf);
    exit(EXIT_SUCCESS);
}

void handle_key(mlx_key_data_t keydata, void *param)
{
    t_fdf *fdf = (t_fdf *)param;

    (void)fdf;
        if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        {
            handle_close(param);
        }   
}

static void error(void)
{
    fprintf(stderr, "%s", mlx_strerror(mlx_errno));
    exit(EXIT_FAILURE);
}

int32_t main(int argc, char **argv)
{
    if (argc != 2)
    {
        write(2, "Usage: ./fdf <map.fdf>\n", 23);
        return 1;
    }

    t_node *map_lines = parse_fdf_map(argv[1]);
    if (!map_lines)
        return (EXIT_FAILURE);
    
    if (!validate_map(map_lines, ' '))
    {
        free_list(map_lines);
        return (EXIT_FAILURE);
    }

    t_map *map = convert_to_map(map_lines);
    if (!map)
    {
        free_list(map_lines);
        return (EXIT_FAILURE);
    }

    printf("Map dimensions: %dx%d, z_min: %d, z_max: %d\n", map->width, map->height, map->z_min, map->z_max);

    t_fdf *fdf = malloc(sizeof(t_fdf));
    if (!fdf)
    {
        fprintf(stderr, "Failed to allocate memory for t_fdf.\n");
        free(map_lines);
        for (size_t y = 0; y < (size_t)map->height; y++)
            free(map->points[y]);
        free(map->points);
        free(map);
        return EXIT_FAILURE;
    }

    fdf->map = map;// Store the map in fdf

    fdf->win = mlx_init(WIDTH, HEIGHT, "fdf", true);
    if (!fdf->win)
    {
        error();
        free(fdf);
        free_list(map_lines);
        for (size_t y = 0; y < (size_t)map->height; y++)
            free(map->points[y]);
        free(map->points);
        free(map);
        return EXIT_FAILURE;
    }
                                                                                                                                                                                                  
    fdf->img = mlx_new_image(fdf->win, WIDTH, HEIGHT);
    if (!fdf->img)
	{
        error();
        mlx_terminate(fdf->win);
        free(fdf);
        free_list(map_lines);
        for (size_t y = 0; y < (size_t)map->height; y++)
            free(map->points[y]);
        free(map->points);
        free(map);
        return EXIT_FAILURE;
    }

    if (mlx_image_to_window(fdf->win, fdf->img, 0, 0) < 0)
    {
        error();
        mlx_delete_image(fdf->win, fdf->img);
        mlx_terminate(fdf->win);
        free(fdf);
        free_list(map_lines);
        for (size_t y = 0; y < (size_t)map->height; y++)
            free(map->points[y]);
        free(map->points);
        free(map);
        return EXIT_FAILURE;
    }
    mlx_key_hook(fdf->win, handle_key, fdf);
    mlx_close_hook(fdf->win, handle_close, fdf);
    mlx_loop(fdf->win);

    mlx_delete_image(fdf->mlx, fdf->img);
    mlx_terminate(fdf->win);

    for (size_t y = 0; y < (size_t)map->height; y++)
        free(map->points[y]);
    free(map->points);
    free(map);
    free(fdf);
    free_list(map_lines);
    handle_close(fdf);
    return (EXIT_SUCCESS);
}


