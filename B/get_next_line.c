#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*line;
	// t_list			*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (fd > 0 && list)
			list = clearnode(create_lst(list));
		return (NULL);
	}
	create_lst(list);
	if (!list)
		return (NULL);
	read_lst(list, fd);
	line = get_lst(list); // ! at this
	if (!line)
	{
		list = clearnode(list);
		return (NULL);
	}
	return (line);
}

t_list	*create_lst(t_list *list)
{
	t_list	*node_c;

	node_c = list;
	while (list)
	{
		if (!node_c)
		{
			node_c = node_lst(&list);
			if (!node_c)
				return (NULL);
			break ;
		}
		node_c = node_c->next;
	}
	return (node_c);
}

t_list	*read_lst(t_list *list, int fd)
{
	int		rd;
	char	*buff;

	rd = 1;
	buff = (char *)malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (1)
	{
		rd = read(fd, buff, BUFFER_SIZE);
		if (rd == -1)
			break ;
		buff[rd] = 0;
		list->content = (ft_strjoin(list->content, buff));
		if (!list->content)
			return (free(buff), NULL);
		if (!check_list(list->content, buff))
			break ;
	}
	free(buff);
	return (list);
}

t_list	*node_lst(t_list **list)
{
	t_list	*new_node;
	t_list	*node_c;

	if (!list)
		return (NULL);
	new_node = (t_list *)malloc(sizeof(t_list)); // new_node //
	if (!new_node)
		return (NULL);
	new_node->content = (char *)malloc(1);
	if (!new_node->content)
		return (free(new_node), NULL);
	new_node->content[0] = 0;
	new_node->next = NULL;
	if (*list == NULL) // lstadd_back //
	{
		*list = new_node;
		return (*list);
	}
	node_c = *list;
	while (node_c->next != NULL)
		node_c = node_c->next;
	node_c->next = new_node;
	return (node_c->next);
}

t_list	*clearnode(t_list *list)
{
	t_list	*tmp_list;
	char	*list_c;
	t_list	*list_n;

	if (!list)
		return (NULL);
	list_c = list->content;
	list_n = list->next;
	if (list_c != NULL)
	{
		free(list_c);
		list_c = NULL;
	}
	if (list_n != NULL)
	{
		tmp_list = list_n;
		free(list);
		list = tmp_list;
	}
	else if (list_n == NULL)
	{
		free(list);
		list = NULL;
	}
	return (list);
}

// #include <fcntl.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int	fd;
// 	char	*line;

// 	fd = open("read_error.txt", O_RDONLY);

// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s\n", line);
// 		free(line);
// 	}
// 	close(fd);
// 	fd = open("43_with_nl.txt", O_RDONLY);

// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s\n", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return 0;
// }
