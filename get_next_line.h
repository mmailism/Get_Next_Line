/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpueankl <kpueankl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:13:01 by kpueankl          #+#    #+#             */
/*   Updated: 2024/01/05 14:46:17 by kpueankl         ###   ########.fr       */
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
void	ft_read_list(t_list **list, int fd);
void	generate_line(t_list *line, char *res);
t_list	*ft_read(t_list *line, int fd, char *buf);
t_list	*ft_create(t_list *line, char *res);
void	ft_create_list(t_list *list, char **res);
int		found_newline(t_list *line);
void	add_join_next(t_list *line, char *buf, int read_list);
t_list	*ft_lstlast(t_list *list);
char	*trim_last_list_element_helper(t_list *last, int i);
void	free_stash(t_list *line);
t_list	*ft_re_list(t_list *line);
// void	ft_re_list(t_list **list);
t_list	*ft_lstnew(char *content);
void	ft_lstadd_back(t_list **list, t_list *new);
t_list	*ft_lstlast(t_list *list);
void	ft_lstclear(t_list **list, void (*del)(void *));
void	*ft_calloc(size_t count, size_t n);
int		ft_new_line(t_list *list);

#endif
