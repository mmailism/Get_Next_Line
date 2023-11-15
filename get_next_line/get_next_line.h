#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE 10
# define BUFFER_SIZE 10

# endif

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

typedef struct	s_list
{
	char			*list;
	struct s_list	*next;
}					t_list;


#endif