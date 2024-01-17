#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*line;
	t_list			*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (fd > 0 && list)
			list = clearnode(list);
		return (NULL);
	}
}
t_list	*newnode_list(t_list **list)
{
	t_list	*new_node;
	t_list	*node_c;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = ()
}