/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:09:43 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/01/24 19:24:33 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//add color range for z min and z max
//implement zoom and rotation, also when rescale window dont lose the map that wasnt painted with the smaller window
//find leaks
//norminnete

// int get_rgba(int r, int g, int b, int a)
// {
//     return (r << 24 | g << 16 | b << 8 | a);
// } 
// int interpolate_color(int start, int end, float progress)
// {
//     int r = (int)(((1 - progress) * ((start >> 16) & 0xFF)) + (progress * ((end >> 16) & 0xFF)));
//     int g = (int)(((1 - progress) * ((start >> 8) & 0xFF)) + (progress * ((end >> 8) & 0xFF)));
//     int b = (int)(((1 - progress) * (start & 0xFF)) + (progress * (end & 0xFF)));

//     return (r << 16 | g << 8 | b);
// }
// void scale_points(t_map *map, float scale_factor)
// {
//     for (int y = 0; y < map->height; y++)
//     {
//         for (int x = 0; x < map->width; x++)
//         {
//             map->points[y][x].x *= scale_factor;
//             map->points[y][x].y *= scale_factor;
//             map->points[y][x].z *= scale_factor;
//         }
//     }
// }

// void rotate_x(t_point *point, double alpha)
// {
//     float temp_y = point->y;
//     float temp_z = point->z;
//     point->y = temp_y * cos(alpha) - temp_z * sin(alpha);
//     point->z = temp_y * sin(alpha) + temp_z * cos(alpha);
// }

// void rotate_y(t_point *point, double beta)
// {
//     float temp_x = point->x;
//     float temp_z = point->z;
//     point->x = temp_x * cos(beta) + temp_z * sin(beta);
//     point->z = -temp_x * sin(beta) + temp_z * cos(beta);
// }

// void rotate_z(t_point *point, double gamma)
// {
//     float temp_x = point->x;
//     float temp_y = point->y;
//     point->x = temp_x * cos(gamma) - temp_y * sin(gamma);
//     point->y = temp_x * sin(gamma) + temp_y * cos(gamma);
// }
// void translate_points(t_map *map, float x_offset, float y_offset)
// {
//     for (int y = 0; y < map->height; y++)
//     {
//         for (int x = 0; x < map->width; x++)
//         {
//             map->points[y][x].x += x_offset;
//             map->points[y][x].y += y_offset;
//         }
//     }
// }

// void transform_point(t_point *point, t_camera *camera)
// {
//     // Apply rotations
//     rotate_x(point, camera->alpha);
//     rotate_y(point, camera->beta);
//     rotate_z(point, camera->gamma);

//     // Apply zoom
//     point->x *= camera->zoom;
//     point->y *= camera->zoom;
//     point->z /= camera->z_divisor; // Scale z-axis separately

//     // Apply offsets
//     point->x += camera->x_offset;
//     point->y += camera->y_offset;
// }