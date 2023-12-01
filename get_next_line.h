/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammai <iammai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:13:01 by kpueankl          #+#    #+#             */
/*   Updated: 2023/12/01 17:01:29 by iammai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h> // del before push

# include <sys/types.h>
# include <sys/vio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 30
# endif

typedef struct s_list
{
    char            *content;
    int             len;
    struct s_list   *next;
}                   t_list;

char    *get_next_line(int fd);
void	ft_switch_list(t_list **list);
void	ft_create_list(t_list *list, char **result);
t_list  *ft_lstnew(char *content);
void    ft_lstadd_back(t_list **list, t_list *new);
t_list  *ft_lstlast(t_list *list);
void    ft_lstclear(t_list **list, void (*del)(void *));
void    ft_bzero(void *s, size_t n);

#endif
