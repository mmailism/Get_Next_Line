/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammai <iammai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:13:01 by kpueankl          #+#    #+#             */
/*   Updated: 2024/01/06 14:50:53 by iammai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <limits.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

char	*get_next_line(int fd);
t_list	*ft_re_list(t_list *line);
t_list	*ft_create(t_list *line, char *res);
t_list	*ft_read(t_list *line, int fd, char *buf);
int		found_newline(t_list *line);
void	free_stash(t_list *line);
char	*trim_last_list_element_helper(t_list *last, int i);
t_list	*ft_lstlast(t_list *list);
void	add_join_next(t_list *line, char *buf, int read_list);
void	generate_line(t_list *line, char *res);

#endif
