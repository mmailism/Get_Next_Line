/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammai <iammai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:13:01 by kpueankl          #+#    #+#             */
/*   Updated: 2023/12/11 20:35:11 by iammai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
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
	t_list	*new_node;
	char	*buf;
	int		read_list;

	read_list = 0;
	while (!ft_new_line(*list))
	{
		buf = NULL;
		new_node = ft_lstnew(buf);
		new_node->content = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
		read_list = read(fd, new_node->content, BUFFER_SIZE);
		if (read_list == 0 || read_list == -1)
		{
			free(new_node->content);
			free(new_node);
			return ;
		}
		new_node->content[BUFFER_SIZE] = '\0';
		ft_lstadd_back(list, new_node);
	}
}

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
	t_list	*lst_s;
	t_list	*new_node;
	char	*content;
	int		i;
	int		k;

	k = 0;
	lst_s = ft_lstlast(*list);
	if (!lst_s)
		return ;
	content = lst_s->content;
	k = lst_s->len;
	lst_s->content = NULL;
	ft_lstclear(list, free);
	if (content[k] != '\0')
	{
		i = 0;
		while (content[k] != '\0')
			content[i++] = content[k++];
		content[i] = '\0';
		new_node = ft_lstnew(content);
		ft_lstadd_back(list, new_node);
	}
	else
		free(content);
}
