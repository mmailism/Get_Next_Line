/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_E.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammai <iammai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:13:01 by kpueankl          #+#    #+#             */
/*   Updated: 2023/12/13 15:11:05 by iammai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	ft_read_list(&list, fd);
	if (!list)
		return (NULL);
	ft_create_list(list, &line);
	ft_re_list(&list);
	return (line);
}

void	ft_read_list(t_list **list, int fd)
{
	char	*buf;
	int		read_list;
	
	read_list = 1;
	
	while (!ft_new_line(*list) && read_list != 0)
	{
		buf = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
		read_list = read(fd, buf, BUFFER_SIZE);
		if (read_list == 0 || read_list == -1)
		{
			free(buf);
			return ;
		}
		buf[read_list] = '\0';
		ft_lstadd_back(list, fd);
		free(buf);
	}
}
	// t_list	*new_node;
	// char	*buf;
	// int		read_list;

	// read_list = 0;
	// while (!ft_new_line(*list))
	// {
	// 	new_node = NULL;
	// 	new_node->content = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	// 	read_list = read(fd, new_node->content, BUFFER_SIZE);
	// 	if (read_list == 0 || read_list == -1)
	// 	{
	// 		free(new_node->content);
	// 		free(new_node);
	// 		return ;
	// 	}
	// 	new_node->content[BUFFER_SIZE] = '\0';
	// 	ft_lstadd_back(list, new_node);
	// }

int	ft_new_line(t_list *list)
{
	int	i;

	list = ft_lstlast(list);
	if (!list)
		return (0);
	i = 0;
	while (list->content[i] != '\0')
	{
		if (list->content[i] == '\n')
		{
			list->len = ++i;
			return (1);
		}
		i++;
	}
	list->len = i;
	return (0);
}

void	ft_create_list(t_list *list, char **line)
{
	int		size_n;
	int		i;
	t_list	*lst_s;

	lst_s = list;
	size_n = 0;
	while (lst_s)
	{
		size_n = size_n + lst_s->len;
		lst_s = lst_s->next;
	}
	if (!size_n)
		return ;
	*line = malloc(sizeof(**line) * (size_n +1));
	if (!line)
		return ;
	size_n = 0;
	while (list && list->content)
	{
		i = 0;
		while (list->content[i] && i < list->len)
			(*line)[size_n++] = list->content[i++];
		list = list->next;
	}
	(*line)[size_n] = '\0';
}

void	ft_re_list(t_list **list)
{
	t_list	*last;
	t_list	*clear_n;
	int		i;
	int		k;

	clear_n = malloc(sizeof(t_list));
	if (list == NULL || clear_n == NULL)
		return ;
	clear_n->next = NULL;
	last = ft_lstlast(*list);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	clear_n->content = malloc(sizeof(char) * i);
	if (clear_n->content == NULL)
		return ;
	k = 0;
	while (last->content[i])
		clear_n->content[k] = '\0';
	ft_lstclear(list, free);
	*list = clear_n;
}
// {
// 	t_list	*lst_s;
// 	// t_list	*new_nodes;
// 	char	*content;
// 	int		i;
// 	int		k;

// 	k = 0;
// 	lst_s = ft_lstlast(*list);
// 	if (!lst_s)
// 		return ;
// 	content = lst_s->content;
// 	k = lst_s->len;
// 	lst_s->content = NULL;
// 	ft_lstclear(list, free);
// 	if (content[k] != '\0')
// 	{
// 		i = 0;
// 		while (content[k] != '\0')
// 			content[i++] = content[k++];
// 		content[i] = '\0';
// 		// new_nodes = ft_lstnew(content);
// 		ft_lstadd_back(list);
// 	}
// 	else
// 		free(content);
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammai <iammai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:13:01 by kpueankl          #+#    #+#             */
/*   Updated: 2023/12/13 15:09:58 by iammai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// void	ft_addlist(t_list **list, char *buf, int read_list)
// {
// 	int		i;
// 	t_list	*last;
// 	t_list	*new_node;

// 	new_node = malloc(sizeof(t_list));
// 	if (new_node == NULL)
// 		return ;
// 	new_node->next = NULL;
// 	new_node->content = malloc(sizeof(char) * (read_list + 1));
// 	if (new_node->content == NULL)
// 		return ;
// 	i = 0;
// 	while (buf[i] && i < read_list)
// 	{
// 		new_node->content[i] = buf[i];
// 		i++;
// 	}
// 	new_node->content[i] = '\0';
// 	if (*list == NULL)
// 	{
// 		*list = new_node;
// 		return ;
// 	}
// 	last = ft_lstlast(*list);
// 	last->next = new_node;
// }

t_list	*ft_lstnew(char *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->len = 0;
	new_node->next = NULL;
	return (new_node);
}

t_list	ft_lstadd_back(t_list *list, int fd)
{
	t_list	*current;
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->len = (char *)ft_calloc(1, 1);
	if (!new_node->len)
	{
		free(new_node);
		return (NULL);
	}
	new_node->len = fd;
	new_node->content = NULL;
	new_node->next = NULL;
	if (*list == NULL)
	{
		*list = new_node;
		return (*list);
	}
	current = *list;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
	return (current->next);
}

t_list	*ft_lstlast(t_list *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

void	ft_lstclear(t_list **list, void (*del)(void *))
{
	t_list	*temp_lst;

	if (!list || !del)
		return ;
	while (*list != NULL)
	{
		temp_lst = *list;
		*list = (*list)->next;
		free(temp_lst->content);
		free(temp_lst);
	}
	*list = NULL;
}

void	*ft_calloc(size_t count, size_t n)
{
	void			*arr;
	size_t			alloc_size;
	size_t			i;
	unsigned char	*cast_s;

	alloc_size = count * n;
	if (!alloc_size || alloc_size / count != n)
		return (NULL);
	arr = malloc(alloc_size);
	if (arr == NULL)
		return (NULL);
	i = 0;
	cast_s = arr;
	while (i < alloc_size)
	{
		cast_s[i] = '\0';
		i++;
	}
	return (cast_s);
}
