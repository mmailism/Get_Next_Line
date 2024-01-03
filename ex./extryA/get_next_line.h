#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_list
{
	char			*str_buf;
	struct s_list	*next;
}					t_list;

char	*get_next_line(int fd);
int	ft_found_newline(t_list *list);
int	ft_len_newline(t_list *list);
t_list	*ft_find_lastnode(t_list *list);
void	ft_copy_str(t_list *list, char *str);
void	dealloc(t_list **list, t_list *clean_node, char *buf);

#endif
