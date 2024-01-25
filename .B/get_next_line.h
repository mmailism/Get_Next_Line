#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <limits.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

char	*get_next_line(int fd);
t_list	*create_lst(t_list *list);
t_list	*read_lst(t_list *list, int fd);
t_list	*node_lst(t_list **list);
t_list	*clearnode(t_list *list);
char	*check_list(char *list, char *buff);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *str, size_t mem);
char	*get_lst(t_list *list);
t_list	*swap_lst(t_list *list, char *lst_n);

#endif