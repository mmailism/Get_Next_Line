#include "get_next_line.h"

char	*ft_strcpy_nl(t_list *lst)
{
	char	*new_line;
	size_t	i;
	size_t	memory;

	if (!lst)
		return (NULL);
	i = 0;
	memory = ft_strlen_nl(lst->data, 2);
	if (memory == 0)
		return (NULL);
	new_line = (char *)malloc(memory + 1);
	if (!new_line)
		return (NULL);
	while (lst->data[i] != '\0' && lst->data[i] != '\n')
	{
		new_line[i] = lst->data[i];
		i++;
	}
	if (lst->data[i] == '\n')
		new_line[i++] = '\n';
	new_line[i] = '\0';
	lst = ft_update_backup(lst, new_line);
	if (!lst)
		return (NULL);
	return (new_line);
}

char	*ft_join_string(char *old_str, char *buf)
{
	char	*temp;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	temp = ft_checkread_malloc_t(old_str, buf, 2);
	if (temp != NULL)
	{
		while (old_str[i] != '\0')
		{
			temp[i] = old_str[i];
			i++;
		}
		while (buf[j] != '\0')
		{
			temp[i] = buf[j];
			i++;
			j++;
		}
		temp[i] = '\0';
	}
	free(old_str);
	return (temp);
}

t_list	*ft_readline(int fd, t_list *lst)
{
	char	*buf;
	int		rd;

	rd = 1;
	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (1)
	{
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd == -1)
			break ;
		buf[rd] = 0;
		lst->data = ft_join_string(lst->data, buf);
		if (!lst->data)
		{
			free(buf);
			return (NULL);
		}
		if (!ft_checkread_malloc_t(lst->data, buf, 1))
			break ;
	}
	free(buf);
	return (lst);
}

t_list	*ft_current_fd(int fd, t_list *lst)
{
	t_list	*current;

	current = lst;
	while (1)
	{
		if (!current)
		{
			current = ft_newnode(fd, &lst);
			if (!current)
				return (NULL);
			break ;
		}
		if (current->fd_id == fd)
			break ;
		current = current->next;
	}
	return (current);
}

char	*get_next_line(int fd)
{
	static t_list	*lst = NULL;
	t_list			*c_lst;
	char			*new_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (fd > 0 && lst)
			lst = ft_clearnode_eof(ft_current_fd(fd, lst));
		return (NULL);
	}
	c_lst = ft_current_fd(fd, lst);
	if (!c_lst)
		return (NULL);
	if (!lst)
		lst = c_lst;
	new_line = ft_strcpy_nl(ft_readline(fd, c_lst));
	if (!new_line)
	{
		lst = ft_clearnode_eof(c_lst);
		return (NULL);
	}
	return (new_line);
}

t_list	*ft_clearnode_eof(t_list *lst)
{
	t_list	*temp;

	if (lst->data != NULL)
	{
		free(lst->data);
		lst->data = NULL;
	}
	lst->fd_id = 0;
	if (lst->next != NULL)
	{
		temp = lst->next;
		free(lst);
		lst = temp;
	}
	else if (lst->next == NULL)
	{
		free(lst);
		lst = NULL;
	}
	return (lst);
}

size_t	ft_strlen_nl(char *s, size_t mode)
{
	size_t	count;

	count = 0;
	if (!s)
		return (0);
	if (mode == 1)
	{
		while (s[count] != '\0')
			count++;
	}
	else if (mode == 2)
	{
		if (s[0] == '\0')
			return (0);
		while (s[count] != '\0' && s[count] != '\n')
			count++;
		if (s[count] == '\n')
			count++;
	}
	return (count);
}

t_list	*ft_update_backup(t_list *c_lst, char *new_line)
{
	char	*temp;
	char	*current;
	size_t	i;
	size_t	count_newmem;

	current = c_lst->data;
	current = current + ft_strlen_nl(current, 2);
	count_newmem = ft_strlen_nl(current, 1);
	temp = (char *)malloc(count_newmem + 1);
	if (!temp)
	{
		free(new_line);
		return (NULL);
	}
	i = 0;
	while (current[i] != '\0')
	{
		temp[i] = current[i];
		i++;
	}
	temp[i] = '\0';
	free(c_lst->data);
	c_lst->data = temp;
	return (c_lst);
}

char	*ft_checkread_malloc_t(char *old_str, char *buf, int mode)
{
	char	*temp;
	size_t	i;
	size_t	count_old_str;
	size_t	count_buf;

	i = 0;
	if (mode == 1)
	{
		if (buf[0] == '\0')
			return (NULL);
		while (buf[i] != '\0')
		{
			if (buf[i] == '\n')
				return (NULL);
			i++;
		}
		return (buf);
	}
	count_old_str = ft_strlen_nl(old_str, 1);
	count_buf = ft_strlen_nl(buf, 1);
	temp = (char *)malloc(count_old_str + count_buf + 1);
	if (!temp)
		return (NULL);
	return (temp);
}

t_list	*ft_newnode(int fd, t_list **lst)
{
	t_list	*current;
	t_list	*n_node;

	n_node = (t_list *)malloc(sizeof(t_list));
	if (!n_node)
		return (NULL);
	n_node->data = (char *)malloc(1);
	if (!n_node->data)
	{
		free(n_node);
		return (NULL);
	}
	n_node->data[0] = 0;
	n_node->fd_id = fd;
	n_node->next = NULL;
	if (*lst == NULL)
	{
		*lst = n_node;
		return (*lst);
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = n_node;
	return (current->next);
}
