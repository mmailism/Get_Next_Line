/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammai <iammai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:13:01 by kpueankl          #+#    #+#             */
/*   Updated: 2023/11/24 17:00:56 by iammai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_create_list(t_list *list, char **result)
{
	t_list	*tmp;
	int		i;
	int		len;

	tmp = list;
	// while (tmp)
	// 	tmp = tmp->next;
	*result = (char *)malloc(sizeof(**result)) + (BUFFER_SIZE + 1);
	if (!result)
		return ;
	len = 0;
	while (list && list->content)
	{
		i = 0;
		while (list->content[i])
			(*result)[len++] = list->content[i++];
		list = list->next;
	}
}

int	ft_found_newline(t_list *list)
{
	int	i;

	i = 0;
	list = ft_lstlast(list);
	if (!list)
		return (0);
	while (list->content[i] != '\0')
	{
		i = 0;
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

static void	ft_read_list(t_list **list, int fd)
{
	t_list	*node_res;
	char	*buf;
	int		read_list;

	read_list = 0;
	buf = (char *)malloc(BUFFER_SIZE + 1);
	ft_bzero(buf, BUFFER_SIZE);
	while (!ft_found_newline(*list))
	{
		node_res = ft_lstnew(buf);
		read_list = read(fd, buf, BUFFER_SIZE);
		if (read_list == 0 || read_list == -1)
		{
			free(buf);
			return ;
		}
		node_res->content[BUFFER_SIZE] = '\0';
		ft_lstadd_back(list, node_res);
	}
}

static void	ft_switch_list(t_list **list)
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
	if (content[k] != '\0')
	{
		i = 0;
		while (content[k] != '\0')
			content[i++] = content[k++];
		new_node = ft_lstnew(content);
		ft_lstadd_back(list, new_node);
	}
	else
		free(content);
}

char	*get_next_line(int fd)
{
	t_list	*list = NULL;
	char	*result;

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

int main()
{
	int fd;
	
	fd = open("59text.txt", O_RDONLY);

	printf("-- out 1 : %s --\n", get_next_line(fd));
	printf("-- out 2 : %s --\n", get_next_line(fd));
	printf("-- out 3 : %s --\n", get_next_line(fd));
	printf("-- out 4 : %s --\n", get_next_line(fd));
	printf("==============\n");
	close (fd);
	return(0);
}
