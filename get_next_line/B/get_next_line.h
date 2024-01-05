/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpueankl <kpueankl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:13:01 by kpueankl          #+#    #+#             */
/*   Updated: 2024/01/05 15:46:57 by kpueankl         ###   ########.fr       */
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
void	*ft_read_file(int fd, t_list **list);
void	ft_add_list(t_list *list, char **line);
void	ft_create_list(t_list *list, char *line);
void	ft_switch_list(t_list **list);
t_list	*ft_lstlast(t_list *list);
void	ft_lstadd_back(t_list **list, char *buf);
void	ft_free_list(t_list *list);
int		ft_strlen(const char *str);
int		ft_strlen(const char *str);

#endif
