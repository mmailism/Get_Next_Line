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
	tmp = create_lst(list);
	if (!tmp)
		return (NULL);
	read_list(tmp, fd);
	extract(list); // ! at this
}

t_list	*create_list(t_list *list)
{
	t_list	*node_c;

	node_c = list;
	while (1)
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

t_list	*read_list(int fd, t_list *list)
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
		list->content = (ft_strjoin(list, buff));
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
	if (!new_node->content)
		return (free(new_node), NULL);
	new_node->content = list;
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
	t_list	*list_c;
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

char	*check_list(char *list, char *buff)
{
	char	*tmp;
	size_t	i;
	size_t	cnt_list_buff;
	size_t	cnt_buff;

	i = 0;
	if (list)
		return (NULL);
	if (list)
	{
		if (buff[0] == '\0')
			return (NULL);
		while (buff[i] != '\0')
		{
			if (buff[i] == '\n')
				return (NULL);
			i++;
		}
		return (buff);
	}
	cnt_list_buff = ft_strlen(list) + ft_strlen(buff);
	// cnt_buff = ft_strlen(buff);
	tmp = (char *)malloc(cnt_list_buff + 1);
	if (!tmp)
		return (free(tmp), NULL);
	return (tmp);
}

// char	*ft_strcpy_nl(t_list *lst)
// {
// 	char	*new_line;
// 	size_t	i;
// 	size_t	memory;

// 	if (!lst)
// 		return (NULL);
// 	i = 0;
// 	memory = ft_strlen_nl(lst->content, 2);
// 	if (memory == 0)
// 		return (NULL);
// 	new_line = (char *)malloc(memory + 1);
// 	if (!new_line)
// 		return (NULL);
// 	while (lst->content[i] != '\0' && lst->content[i] != '\n')
// 	{
// 		new_line[i] = lst->content[i];
// 		i++;
// 	}
// 	if (lst->content[i] == '\n')
// 		new_line[i++] = '\n';
// 	new_line[i] = '\0';
// 	lst = ft_update_backup(lst, new_line);
// 	if (!lst)
// 		return (NULL);
// 	return (new_line);
// }

// t_list	*ft_update_backup(t_list *c_lst, char *new_line)
// {
// 	char	*temp;
// 	char	*current;
// 	size_t	i;
// 	size_t	count_newmem;

// 	current = c_lst->content;
// 	current = current + ft_strlen_nl(current, 2);
// 	count_newmem = ft_strlen_nl(current, 1);
// 	temp = (char *)malloc(count_newmem + 1);
// 	if (!temp)
// 	{
// 		free(new_line);
// 		return (NULL);
// 	}
// 	i = 0;
// 	while (current[i] != '\0')
// 	{
// 		temp[i] = current[i];
// 		i++;
// 	}
// 	temp[i] = '\0';
// 	free(c_lst->content);
// 	c_lst->content = temp;
// 	return (c_lst);
// }
