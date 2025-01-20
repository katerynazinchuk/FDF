/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:58:07 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/01/20 18:52:24 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* drawing line function (google Bresenham algorithm)
**		- find by how much we need to increase x and by how much we need to increase y
**			by using float. Example:
**				x = 2; x1 = 4;
**				y = 2; y1 = 6;
**				steps for x: 2
**				steps for y: 4
**				that means that y should grow 2 times faster than x
**				every loop step: y += 1 and x += 0.5
**				after 4 steps x and y will be equal with x1, y1
**
**					real x:y		x:y     pixels				
**			start:		2.0 : 2.0		2:2        .
**			step1:		2.5 : 3.0		2:3        .
**			step2:		3.0 : 4.0		3:4         .
**			step3:		3.5 : 5.0		3:5         .
**			step4:		4.0 : 6.0		4:6          .
**
**				that works because (float)2.5 turns to (int)2 in func. mlx_pixel_put()
**	--------------
**	3. function which draws lines between every dot
**		- example:
**				0->		0->		0->		0
**				|		|		|		|
**				
**				0->		10->            10->            0
**				|		|		|		|
**				
**				0->		10->            10->            0
**				|		|		|		|
**				
**				0->		0->		0->		0
**			'->' and '|'are lines between dots 
**			every dot has two lines (right and down):	0->
**                                                                      |
*/
#include <fdf.h>

typedef struct s_render_data {
    void    *mlx_ptr;
    void    *win_ptr;
}               t_render_data;

/**
 * Draws a line from (x0, y0) to (x1, y1) using the Bresenham algorithm.
 * 
 * @param data Pointer to the rendering data structure containing mlx and window pointers.
 * @param x0 Starting x-coordinate of the line.
 * @param y0 Starting y-coordinate of the line.
 * @param x1 Ending x-coordinate of the line.
 * @param y1 Ending y-coordinate of the line.
 */
void    draw_line(t_render_data *data, int x0, int y0, int x1, int y1)
{
    float   dx;
    float   dy;
    float   step;
    float   x;
    float   y;
    int     i;

    dx = x1 - x0;
    dy = y1 - y0;
    step = fmax(fabs(dx), fabs(dy));
    dx /= step;
    dy /= step;
    x = x0;
    y = y0;
    i = 0;
/**
 * Draws a grid based on the provided 2D array.
 * 
 * @param data Pointer to the rendering data structure.
 * @param grid 2D array representing the grid.
 * @param rows Number of rows in the grid.
 * @param cols Number of columns in the grid.
 */
void    draw_grid(t_render_data *data, int **grid, int rows, int cols)
{
        mlx_pixel_put(data->x, data->y, round(x), round(y), 0xFFFFFF);
        x += dx;
        y += dy;
        i++;
        }
}


void    draw_grid(t_render_data *data, int **grid, int rows, int cols)
{
    int     x;
    int     y;

    y = 0;
    while (y < rows)
    {
        x = 0;
        while (x < cols)
        {
            if (x < cols - 1)
                draw_line(data, x, y, x + 1, y);
            if (y < rows - 1)
                draw_line(data, x, y, x, y + 1);
            x++;
        }
        y++;
    }
}
//--------------------------------------------------------------------------//
void apply_isometric_projection(t_point *point, float angle)
{
    float prev_x = point->x;
    float prev_y = point->y;
    point->x = (prev_x - prev_y) * cos(angle);
    point->y = (prev_x + prev_y) * sin(angle) - point->z;
}

// Helper function to draw a single pixel
void draw_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
    if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
        mlx_put_pixel(img, x, y, color);
}

// Bresenham's line-drawing algorithm
void draw_line(mlx_image_t *img, t_point start, t_point end)
{
    int dx = fabs(end.x - start.x);
    int dy = fabs(end.y - start.y);
    int sx = (start.x < end.x) ? 1 : -1;
    int sy = (start.y < end.y) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        draw_pixel(img, (int)start.x, (int)start.y, start.color);
        if ((int)start.x == (int)end.x && (int)start.y == (int)end.y)
            break;
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            start.x += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            start.y += sy;
        }
    }
}

// Draw lines between points
void draw_map(t_fdf *fdf, float angle)
{
    t_map *map = fdf->map;
    for (int y = 0; y < map->height; y++)
    {
        for (int x = 0; x < map->width; x++)
        {
            t_point start = map->points[y][x];
            apply_isometric_projection(&start, angle);

            if (x + 1 < map->width)
            {
                t_point end = map->points[y][x + 1];
                apply_isometric_projection(&end, angle);
                draw_line(fdf->img, start, end);
            }

            if (y + 1 < map->height)
            {
                t_point end = map->points[y + 1][x];
                apply_isometric_projection(&end, angle);
                draw_line(fdf->img, start, end);
            }
        }
    }
}
