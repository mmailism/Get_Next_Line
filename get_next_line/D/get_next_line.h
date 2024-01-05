/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpueankl <kpueankl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:13:01 by kpueankl          #+#    #+#             */
/*   Updated: 2024/01/05 15:58:07 by kpueankl         ###   ########.fr       */
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
size_t	find_line_ending(char *str, size_t i);
char	*get_string(char *str);
char	*read_the_line(char *str);
char	*free_and_null(char *buff1, char *buff2);
char	*ft_strjoin(char *buffer, char *content);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *str, int c);
size_t	ft_strlen(const char *str);

#endif
