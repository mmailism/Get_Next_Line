#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

typedef	struct s_list
{
	char			*str_buf;
	struct s_list	*next;
}					t_list;

	char	*get_next_line(int fd);
	int		ft_len_newline(t_list *list);
	void	ft_copy_str(t_list *list, char *str);
	void	dealloc(t_list **list, t_list *clean_node, char *buf);
	int		ft_found_newline(t_list *list);
	t_list	*ft_find_last_node(t_list *list);

#endif