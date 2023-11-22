#include "get_next_line.h"

void	ft_create_list(t_list *list, char **result)
{
}

void	ft_read_list(t_list **list, int fd)
{
	t_list *node_res;
	char    *buf;
	int     read_list;

	read_list = 0;
	buf = (char *)malloc(BUFFER_SIZE + 1)
	ft_bzero(buf, BUFFER_SIZE);
	while (!ft_newline(*list))
	{
		node_res = ft_lstnew(buf);
		read_list = read(fd, buf, BUFFER_SIZE);
		if (read_list <= 0)
		{
			free(buf);
			return ;
		}
		node_res->content[BUFFER_SIZE] = '\0';
		ft_lstadd_back(list, node_res);
	}
}

char	*get_next_line(int fd)
{
	static t_list   *list = NULL;
	char            *result;

	result = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ft_read_list(&list, fd);
	if(!list)
		return (NULL);
	ft_create_list(list, &result);
	ft_switch_list(&list);
	return (result);
}