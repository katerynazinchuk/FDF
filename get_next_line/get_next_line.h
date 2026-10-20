/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:30:23 by kzinchuk          #+#    #+#             */
/*   Updated: 2024/11/30 11:27:50 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}		t_list;

char	*get_next_line(int fd);
int		found_newline(t_list *node_list);
t_list	*get_last_in_list(t_list *node_list);
void	read_and_store(int fd, t_list **node_list);
void	*add_to_node_list(t_list **node_list, char *buf, int readed);
void	extract_line(t_list *node_list, char **line);
void	allocate_line(char **line, t_list *node_list);
int		clean_node_list(t_list **node_list);
void	free_node_list(t_list **node_list);
t_list	*create_node(ssize_t content_size);

#endif