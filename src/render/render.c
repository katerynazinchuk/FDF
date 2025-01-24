/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:58:07 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/01/24 19:18:38 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void calculate_offsets(t_fdf *fdf, int *offset_x, int *offset_y)
{

    int center_x = fdf->map->width * GRIDSPASE / 2;
    int center_y = fdf->map->height * GRIDSPASE / 2;

    *offset_x = center_x;
    *offset_y = center_y;
}

t_line new_line(t_render_point start, t_render_point end)
{
    t_line line;
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
    
    return line;
}

t_render_point project_isometric(t_point point, int offset_x, int offset_y, float angle)
{
    t_render_point result;
    result.x = (int)((point.x - point.y) * cos(angle)) + offset_x;
    result.y = (int)((point.x + point.y) * sin(angle) - point.z) + offset_y;
    result.color = point.color;

    return result;
}

void bresenham_line(t_fdf *fdf, t_render_point start, t_render_point end)
{
    uint32_t color;
    t_line line = new_line(start, end);
    if(start.color !=0)
        color = start.color;
    else
        color = 0xFFFF00FF;
    while (1)
    {
        if (start.x >= 0 && start.x < (int)fdf->img->width && start.y >= 0 && start.y < (int)fdf->img->height)
            mlx_put_pixel(fdf->img, start.x, start.y, color);
        if (start.x == end.x && start.y == end.y)
            break;
        int e2 = 2 * line.err;
        if (e2 > -line.dy)
        {
            line.err -= line.dy;
            start.x += line.sx;
        }
        if (e2 < line.dx)
        {
            line.err += line.dx;
            start.y += line.sy;
        }
    }
}

static void draw_horizontal_lines(t_fdf *fdf, int offset_x, int offset_y, float angle)
{
    int y = 0;
    while (y < fdf->map->height)
    {
        int x = 0;
        while (x + 1 < fdf->map->width)
        {
            t_render_point start = project_isometric(fdf->map->points[y][x], offset_x, offset_y, angle);
            t_render_point end = project_isometric(fdf->map->points[y][x + 1], offset_x, offset_y, angle);
            bresenham_line(fdf, start, end);
            x++;
        }
        y++;
    }
}

static void draw_vertical_lines(t_fdf *fdf, int offset_x, int offset_y, float angle)
{
    int x = 0;
    while (x < fdf->map->width)
    {
        int y = 0;
        while (y + 1 < fdf->map->height)
        {
            t_render_point start = project_isometric(fdf->map->points[y][x], offset_x, offset_y, angle);
            t_render_point end = project_isometric(fdf->map->points[y + 1][x], offset_x, offset_y, angle);
            bresenham_line(fdf, start, end);
            y++;
        }
        x++;
    }
}

void render_top_view(t_fdf *fdf)
{
    int offset_x, offset_y;
    float angle = 0.8;

    offset_x = fdf->offset_x;
    offset_y = fdf->offset_y;

    draw_horizontal_lines(fdf, offset_x, offset_y, angle);
    draw_vertical_lines(fdf, offset_x, offset_y, angle);
}
