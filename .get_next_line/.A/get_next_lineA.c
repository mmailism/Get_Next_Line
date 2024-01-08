/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpueankl <kpueankl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:13:01 by kpueankl          #+#    #+#             */
/*   Updated: 2024/01/05 15:26:15 by kpueankl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_create_list(t_list *list, char **res)
{
	int		len;
	int		i;
	t_list	*tmp;

	tmp = list;
	while (tmp)
		tmp = tmp->next;
	*res = (char *)malloc(sizeof(**res));
	if (!res)
		return ;
	len = 0;
	while (list && list->content)
	{
		i = 0;
		while (list->content[i])
			(*res)[len++] = list->content[i++];
		list = list->next;
	}
}

void	ft_switch_list(t_list **list)
{
	t_list	*last;
	t_list	*clear_node;
	int		i;
	int		j;

	clear_node = malloc(sizeof(t_list));
	if (list == NULL || clear_node == NULL)
		return ;
	clear_node->next = NULL;
	last = ft_lstlast(*list);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content[i] && last->content[i] != '\n')
		i++;
	clear_node->content = malloc(sizeof(char) * ((ft_strlen(last->content) - i) + 1));
	if (clear_node->content == NULL)
		return ;
	j = 0;
	while (last->content[i])
		clear_node->content[j++] = last->content[i++];
	clear_node->content[j] = '\0';
	ft_free_list(list);
	*list = clear_node;
}

int	ft_find_newline(t_list *list)
{
	int		i;
	int		k;
	char	*str;
	
	if (!list)
		return (0);
		while (list->content[i] != '\0')
	{
		if (list->content[i] == '\n')
		{
			list->len = i++;
			return(i);
		}
		i++;
	}
	list->len = i;
	return (i);
}

void	ft_read_file(t_list **list, int fd)
{
	t_list	*node_s;
	char	*buf;
	int		read_file;

	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	ft_bzero(buf, BUFFER_SIZE);
	while (!ft_find_newline(*list) && read_file != 0)
	{
		node_s = ft_lstnew(buf);
		printf("TEST\n");
		read_file = read(fd ,buf, BUFFER_SIZE);
		if ((*list == NULL && read_file == 0) || read_file == -1)
		{
			free(buf);
			return ;
		}
		node_s->content[BUFFER_SIZE] = '\0';
		ft_lstadd_back(list, node_s);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*res;

	res = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ft_read_file(&list, fd);
	if (!list)
	{
		free(list);
		return (NULL);
	}
	ft_create_list(list, &res);
	ft_switch_list(&list);
	return (res);
}

// int main()
// {
// 	int fd;
	
// 	fd = open("43_with_nl.txt", O_RDONLY);

// 	printf("-- out 1 : %s --\n", get_next_line(fd));
// 	printf("-- out 2 : %s --\n", get_next_line(fd));
// 	printf("-- out 3 : %s --\n", get_next_line(fd));
// 	printf("-- out 4 : %s --\n", get_next_line(fd));
// 	printf("============================\n");
// 	close (fd);
// 	return(0);
// }
