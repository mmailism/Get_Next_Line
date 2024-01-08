/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammai <iammai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:13:01 by kpueankl          #+#    #+#             */
/*   Updated: 2024/01/06 18:03:19 by iammai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
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
char	*create_list(char *read_buf);
char	*get_list(char *read_buf);
char	*ft_strjoin(char *buffer, char *content);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *str);
void	*ft_memmove(void *dst, const void *src, size_t n);
char	*free_and_null(char *buff1, char *buff2);
void	*ft_memcpy(void *to, const void *from, size_t n);
char	*ft_strchr(const char *s, int c);
size_t	find_lastline(char *read_buf, size_t i);

#endif