/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammai <iammai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:13:01 by kpueankl          #+#    #+#             */
/*   Updated: 2024/01/31 14:15:57 by iammai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <limits.h>

char	*get_next_line(int fd);
char	*read_line(int fd, char *buffer, char **addr_list, int rd);
char	*get_list(char *list);
char	*get_newline(char *str);
size_t	ft_strlen(char *str, size_t mem);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *tmp, char *buff);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(char *s);
char	*set_zero(char *ptr, size_t mem);

#endif
