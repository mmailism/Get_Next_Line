/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpueankl <kpueankl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:13:01 by kpueankl          #+#    #+#             */
/*   Updated: 2024/01/05 16:57:21 by kpueankl         ###   ########.fr       */
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
	int				*len;
	struct s_list	*next;
}					t_list;

char	*get_next_line(int fd);
void	prepare_stash_from_file(int fd, t_list **stash);
void	append_buffer_to_stash(t_list **stash, char *buffer, int num_bytes);
void	read_line_from_stash(t_list *stash, char **line);
t_list	*trim_last_list_element(t_list **lst);
t_list	*ft_lstlast(t_list *lst);
char	*trim_last_list_element_helper(t_list *last, int i);
int		found_new_line(t_list *stash);
void	generate_line(char **line, t_list *stash);
void	free_stash(t_list *stash);

#endif
