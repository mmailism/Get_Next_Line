#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 3

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