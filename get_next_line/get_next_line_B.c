/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_B.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpueankl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:13:14 by kpueankl          #+#    #+#             */
/*   Updated: 2023/11/20 15:13:17 by kpueankl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstnew(char *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd_back(t_list **list, t_list *new)
{
	t_list	*temp;

	if (!list || !new)
		return ;
	if (!(*list))
	{
		*list = new;
		return ;
	}
	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

t_list	*ft_lstlast(t_list *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	ft_lstclear(t_list **list, void (*del)(void *))
{
	if (!list || !del || !(*list))
		return ;
	ft_lstclear(&(*list)->next, del);
	del((*list)->content);
	free(*list);
	*list = NULL;
}

int	ft_find_newline(t_list *list)
{
	int		i;

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
	return (i);
}

void	ft_read_list(t_list **list, int fd)
{
	t_list		*new_node;
	char		*buf;
	static int	read_list = 0;

	while (!ft_find_newline(*list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		new_node = ft_lstnew(buf);
		read_list = read(fd, buf, BUFFER_SIZE);
		if (read_list == 0 || read_list == -1)
		{
			free(new_node);
			return ;
		}
		new_node->content[BUFFER_SIZE] = '\0';
		ft_lstadd_back(list, new_node);
	}
}

void	ft_create_list(t_list *list, char **result)
{
	int		len;
	int		i;
	t_list	*tmp;

	tmp = list;
	len = 0;
	while (tmp)
	{
		len = len + tmp->len;
		tmp = tmp->next;
	}
	*result = malloc(sizeof(**result) + (len + 1));
	if (!result)
		return ;
	len = 0;
	while (list && list->content)
	{
		i = 0;
		while (list->content[i] && i < list->len)
			(*result)[len++] = list->content[++i];
		list = list->next;
	}
	(*result)[len] = '\0';
}

void	ft_switch_list(t_list **list)
{
	t_list	*tmp;
	t_list	*new_node;
	char	*content;
	int		i;
	int		k;

	k = 0;
	tmp = ft_lstlast(*list);
	if (!tmp)
		return ;
	content = tmp->content;
	k = tmp->len;
	tmp->content = NULL;
	ft_lstclear(list, free);
	i = 0;
	if (content[k] != '\0')
	{
		while (content[k] != '\0')
			content[i++] = content[++k];
		content[i] = '\0';
		new_node = ft_lstnew(content);
		ft_lstadd_back(list, new_node);
	}
	else
		free(content);
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*result;

	result = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ft_read_list(&list, fd);
	// if (!list)
	// 	return (NULL);
	ft_create_list(list, &result);
	ft_switch_list(&list);
	return (result);
}

int	main(void)
{
	int	fd = open("59text.txt", O_RDONLY);

	printf("test1 :%s\n", get_next_line(fd));
	printf("test2 :%s\n", get_next_line(fd));
	printf("test3 :%s\n", get_next_line(fd));
	printf("test4 :%s\n", get_next_line(fd));
	close (fd);
	return(0);
}
