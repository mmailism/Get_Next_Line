/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammai <iammai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:13:28 by kpueankl          #+#    #+#             */
/*   Updated: 2023/11/22 18:06:37 by iammai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 4

# endif

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

typedef struct	s_list
{
	char			*content;
	struct s_list	*next;
	int				len;
}					t_list;
char	*get_next_line(int fd);

#endif
