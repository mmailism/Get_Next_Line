#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
# endif

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

typedef	struct s_list
{
	char			*content;
	int				length;
	struct s_list	*next;
}					t_list;
	char	*get_next_line(int fd);
	
#endif
