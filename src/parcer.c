/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:08:58 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/01/18 18:58:32 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// static t_map *initialize_map(void)
// {
//     t_map *map = malloc(sizeof(t_map));
//     if (!map)
//     {
//         perror("Error allocating memory for t_map");
//         return NULL;
//     }
//     map->z_min = INT32_MAX;
//     map->z_max = INT32_MIN;
//     map->height = 0;
//     map->width = 0;
//     map->points = NULL;
//     return map;
// }

// static int determine_width(const char *line)
// {
//     char **split = ft_split(line, ' ');
//     if (!split)
//         return -1;

//     int width = 0;
//     while (split[width])
//         width++;

//     int i = 0;
//     while (split[i])
//         free(split[i++]);
//     free(split);

//     return width;
// }
// static void cleanup_map_on_error(t_map *map, int fd)
// {
//     if (map)
//     {
//         for (int i = 0; i < map->height; i++)
//             free(map->points[i]);
//         free(map->points);
//         free(map);
//     }
//     if (fd >= 0)
//         close(fd);
// }

// t_map *parse_map(const char *filename)
// {
//     int fd = open(filename, O_RDONLY);
//     if (fd < 0)
//     {
//         perror("Error opening file");
//         return NULL;
//     }

//     t_map *map = initialize_map();
//     if (!map)
//     {
//         close(fd);
//         return NULL;
//     }

//     char *line = NULL;
//     int row = 0;
//     t_iterator iter = {0, 0};

//     line = get_next_line(fd);
//     if (!line)
//     {
//         cleanup_map_on_error(map, fd);
//         return NULL;
//     }

//     map->width = determine_width(line);
//     if (map->width <= 0)
//     {
//         free(line);
//         cleanup_map_on_error(map, fd);
//         return NULL;
//     }
//     free(line);
//     while ((line = get_next_line(fd)) != NULL)
//     {
//         char **split = ft_split(line, ' ');
//         if (!split)
//         {
//             free(line);
//             continue;
//         }

//         map->height++;
//         map->points = realloc(map->points, sizeof(t_point *) * map->height);
//         if (!map->points)
//         {
//             iter.i = 0;
//             while (iter.i < map->height - 1)
//                 free(map->points[iter.i++]);
//             free(map->points);
//             free(map);
//             close(fd);
//             return NULL;
//         }

//         map->points[row] = malloc(sizeof(t_point) * map->width);
//         if (!map->points[row])
//         {
//             iter.i = 0;
//             while (iter.i < row)
//                 free(map->points[iter.i++]);
//             free(map->points);
//             free(map);
//             close(fd);
//             return NULL;
//         }
//         int col = 0;
//         while (col < map->width)
//         {
//             char **value_parts = ft_split(split[col], ',');
//             if (!value_parts)
//             {
//                 perror("Error splitting z and color");
//                 free(split[col]);
//                 continue;
//             }

//             map->points[row][col].z = atoi(value_parts[0]);
//             map->points[row][col].color = value_parts[1]
//                 ? strtol(value_parts[1], NULL, 16)
//                 : 0xFFFFFF;

//             iter.i = 0;
//             while (value_parts[iter.i])
//                 free(value_parts[iter.i++]);
//             free(value_parts);

//             if (map->points[row][col].z < map->z_min)
//                 map->z_min = map->points[row][col].z;
//             if (map->points[row][col].z > map->z_max)
//                 map->z_max = map->points[row][col].z;

//             col++;
//         }

//         iter.j = 0;
//         while (split[iter.j])
//             free(split[iter.j++]);
//         free(split);
//         free(line);
//         row++;
//     }

//     close(fd);

//     if (map->height == 0 || map->width == 0)
//     {
//         free(map);
//         return NULL;
//     }
//   printf("%d rows were found\n", map->height);
//     printf("%d columns were found\n", map->width);
//     printf("2D map was stored\n");
//     for (int i = 0; i < map->height; i++)
//     {
//     for (int j = 0; j < map->width; j++)
//     {
//         printf("%d ", (int)map->points[i][j].z);
//     }
//     printf("\n");
//     }
//     return map;
// }

// static t_map *initialize_map(void)
// {
//     t_map *map = malloc(sizeof(t_map));
//     if (!map)
//     {
//         perror("Error allocating memory for t_map");
//         return NULL;
//     }
//     map->z_min = INT32_MAX;
//     map->z_max = INT32_MIN;
//     map->height = 0;
//     map->width = 0;
//     map->points = NULL;
//     return map;
// }

// t_map *parse_map(const char *filename)
// {
//     int fd = open(filename, O_RDONLY);
//     if (fd < 0)
//     {
//         perror("Error opening file");
//         return NULL;
//     }
//     t_map *map = initialize_map();
//     if (!map)
//     {
//         close(fd);
//         return NULL;
//     }
//     char *line = NULL;
//     int row = 0;
//     t_iterator iter = {0, 0};
//     while ((line = get_next_line(fd)) != NULL)
//     {
//         char **split = ft_split(line, ' ');
//         if (!split)
//         {
//             free(line);
//             continue;
//         }
//         if (map->height == 0)
//         {
//             while (split[map->width])
//                 map->width++;
//             map->points = malloc(sizeof(t_point *) * 1);
//             if (!map->points)
//             {
//                 iter.j = 0;
//                 while (split [iter.j])
//                     free(split[iter.j++]);
//                 free(split);
//                 free(line);
//                 free(map);
//                 close(fd);
//                 return NULL;
//             }
//         }
//         map->height++;
//         map->points = realloc(map->points, sizeof(t_point *) * map->height);
//         if (!map->points)
//         {
//             iter.i = 0;
//             while(iter.i < map->height - 1)
//                 free(map->points[iter.i++]);
//             free(map->points);
//             free(map);
//             close(fd);
//             return NULL;
//         }
//         map->points[row] = malloc(sizeof(t_point) * map->width);
//         if (!map->points[row])
//         {
//             iter.i = 0;
//             while (iter.i < row)
//                 free(map->points[iter.i++]);
//             free(map->points);
//             free(map);
//             close(fd);
//             return NULL;
//         }
//         int col = 0;
//         while (col < map->width)
//         {
//             char **value_parts = ft_split(split[col], ',');
//             if (!value_parts)
//             {
//                 perror("Error splitting z and color");
//                 free(split[col]);
//                 iter.j = 0;
//                 while (split[iter.j])
//                     free(split[iter.j++]);
//                 free(split);
//                 free(line);
//                 close(fd);
//                 return NULL;
//             }
//             map->points[row][col].z = atoi(value_parts[0]);
//             if (value_parts[1])
//                 map->points[row][col].color = strtol(value_parts[1], NULL, 16);
//             else 
//                 map->points[row][col].color = 0xFFFFFF;
//             iter.i = 0;
//             while (value_parts[iter.i])
//                 free(value_parts[iter.i++]);
//             free(value_parts);
//             if (map->points[row][col].z < map->z_min)
//                 map->z_min = map->points[row][col].z;
//             if (map->points[row][col].z > map->z_max)
//                 map->z_max = map->points[row][col].z;
//             col++;
//         }
//         iter.j = 0;
//         while (split[iter.j])
//             free(split[iter.j++]);
//         free(split);
//         free(line);
//         row++;
//     }
//     if (map->height == 0 || map->width == 0)
//     {
//         free(map);
//         close(fd);
//         return NULL; // Invalid map
//     }
//     close(fd);
//     // printf("%d rows were found\n", map->height);
//     // printf("%d columns were found\n", map->width);
//     // printf("2D map was stored\n");
//     // for (int i = 0; i < map->height; i++)
//     // {
//     // for (int j = 0; j < map->width; j++)
//     // {
//     //     printf("%d ", (int)map->points[i][j].z);
//     // }
//     // printf("\n");
//     // }
//     return map;
// }

