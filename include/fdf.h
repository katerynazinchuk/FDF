/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:22:54 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/01/24 19:21:15 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <MLX42/MLX42_Int.h>
# include "MLX42/MLX42.h"
# include <math.h>
# include <fcntl.h>
# include "get_next_line.h"
# include "libft.h"

# define WIDTH 2000
# define HEIGHT 1000
# define GRIDSPASE 50
// # define COLOR 0x00FF00FF
// # define ZOOM_STEP 1.1
// #define ROT_STEP M_PI / 24

typedef struct s_node
{
    char			*line;
    struct s_node	*next;
}					t_node;

typedef struct s_point {
    float		x;
    float		y;
    float		z;
    uint32_t	color;
}				t_point;

typedef struct s_map {
    t_point	**points;
    int32_t	width;
    int32_t	height;
    int32_t	z_min;
    int32_t	z_max;
    int32_t	color_range;
}			t_map;


typedef struct s_fdf
{
    void		*win;
    mlx_t		*mlx;
    mlx_image_t	*img;
    t_map		*map;
    int			offset_x;
    int			offset_y;
}				t_fdf;


typedef struct s_render_point {
    int			x;
    int			y;
    int         z;
    uint32_t	color;
}				t_render_point;

typedef struct s_render_data {
    void	*mlx_ptr;
    void	*win_ptr;
}			t_render_data;

typedef struct s_line
{
    int	dx;
    int	dy;
    int	sx;
    int	sy;
    int err;
}		t_line;


t_node *add_node(char *line);
t_node *list_append(t_node **head, char *line);
void free_list(t_node *head);
t_node *read_fdf_map(const char *filename);
size_t count_strings(const char *s, char delimiter);
int validate_map(t_node *map_lines, char delimiter);
t_map *initialize_map(t_node *map_lines);
t_map *populate_map(t_map *map, t_node *map_lines);
t_map *convert_to_map(t_node *map_lines);

void render_top_view(t_fdf *fdf);
void bresenham_line(t_fdf *fdf, t_render_point start, t_render_point end);

void handle_key_input(mlx_key_data_t keydata, void *param);
void handle_close(void *param);
void handle_escape(mlx_key_data_t keydata, void *param);
void error(void);

void calculate_offsets(t_fdf *fdf, int *offset_x, int *offset_y);
int hex_to_int(const char *hex);
int ft_abs(int n);




#endif