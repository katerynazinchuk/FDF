/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:22:54 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/03/12 16:55:18 by kzinchuk         ###   ########.fr       */
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

# define WIDTH 2500
# define HEIGHT 2000
# define GRIDSPASE 5
# define COLOR 0x00FF00FF
// # define ZOOM_STEP 1.1
// #define ROT_STEP M_PI / 24

typedef struct s_node
{
	char			*line;
	struct s_node	*next;
}					t_node;

typedef struct s_point
{
	float		x;
	float		y;
	float		z;
	uint32_t	color;
}				t_point;

typedef struct s_map
{
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

typedef struct s_render_point
{
	int			x;
	int			y;
	int			z;
	uint32_t	color;
}				t_render_point;

typedef struct s_render_data
{
	void	*mlx_ptr;
	void	*win_ptr;
}			t_render_data;

typedef struct s_line
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
}		t_line;

typedef struct s_color
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;
}	t_color;

typedef struct s_bresenham
{
	t_line			line;
	t_render_point	start;
	t_render_point	end;
	uint32_t		color_start;
	uint32_t		color_end;
	int				total_steps;
	int				current_step;
}	t_bresenham;

int				validate_arguments(int argc);
t_map			*validate_and_store_map(const char *filename, \
											t_node **map_lines);
void			start_mlx_loop(t_fdf *fdf);
t_node			*add_node(char *line);
t_node			*list_append(t_node **head, char *line);
void			free_list(t_node *head);
t_fdf			*initialize_fdf(t_map *map, t_node *map_lines);
t_node			*read_fdf_map(const char *filename);
size_t			count_strings(const char *s, char delimiter);
int				validate_map(t_node *map_lines, char delimiter);
t_map			*initialize_map(t_node *map_lines);
t_map			*populate_map(t_map *map, t_node *map_lines);
t_map			*convert_to_map(t_node *map_lines);
void			render_top_view(t_fdf *fdf);
void			handle_close(void *param);
void			handle_key(mlx_key_data_t keydata, void *param);
void			error(void);
void			handle_error(t_fdf *fdf, t_node *map_lines, t_map *map);
//render
t_render_point	project_isometric(t_point point, float angle, t_fdf *fdf);
void			bresenham(t_fdf *fdf, t_render_point start, t_render_point end);
void			render_top_view(t_fdf *fdf);
void			calculate_offsets(t_fdf *fdf);
int				ft_abs(int n);
t_line			new_line(t_render_point start, t_render_point end);
int				hex_to_int(const char *hex);
int				ft_abs(int n);
//key_controls
void			clear_and_render(t_fdf *fdf);// ?????
//color
t_color			extract_color(uint32_t color);
uint32_t		combine_color(t_color result);
uint32_t		interpolate_color(uint32_t start_color, uint32_t end_color, \
													float t);
uint32_t		calculate_gradient_color(t_map *map, int32_t z);

#endif