/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_A.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpueankl <kpueankl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:13:01 by kpueankl          #+#    #+#             */
/*   Updated: 2023/11/20 16:23:58 by kpueankl         ###   ########.fr       */
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

// t_list	*ft_lstlast(t_list *list)
// {
// 	if (list == NULL)
// 		return (NULL);
// 	while (list->next)
// 		list = list->next;
// 	return (list);
// }

// void	ft_lstclear(t_list **list, void (*del)(void *))
// {
// 	if (!list || !del || !(*list))
// 		return ;
// 	ft_lstclear(&(*list)->next, del);
// 	del((*list)->content);
// 	free(*list);
// 	*list = NULL;
// }

void	ft_create_list(t_list *list, char **res)
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
	*res = malloc(sizeof(**res) + (len + 1));
	if (!res)
		return ;
	len = 0;
	while (list && list->content)
	{
		i = 0;
		while (list->content[i] && i < list->len)
			(*res)[len++] = list->content[++i];
		list = list->next;
	}
	(*res)[len] = '\0';
}

// void	ft_switch_list(t_list **list)
// {
// 	t_list	*tmp;
// 	t_list	*new_node;
// 	char	*content;
// 	int		i;
// 	int		k;

// 	k = 0;
// 	if (!tmp)
// 		return ;
// 	tmp = ft_lstclear(list, free);
// 	tmp->content = NULL;
// 	i = 0;
// 	if (content[k] != '\0')
// 	{
// 		while (content[k] != '\0')
// 			content[i++] = content[++k];
// 		content[i] = '\0';
// 	}
// 	else
// 		free(content);
// }

void	ft_read_file(t_list **list, int fd)
{
	t_list		*node_s;
	char		*buf;
	static int	read_file = 0;

	printf("==fd==%d\n",fd);
	
	buf = (char *)malloc(BUFFER_SIZE + 1);
	read_file = read(fd ,buf, BUFFER_SIZE);
	
	printf("\nread_file=%d\nbuf=%s\n", read_file, buf);

	node_s = ft_lstnew(buf);
	if (read_file == 0 || read_file == -1)
		{
			free(node_s);
			return ;
		}
	ft_lstadd_back(list, node_s);
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*res;

	if (fd <= 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ft_read_file(&list, fd);
	ft_create_list(list, &res);
	// ft_switch_list(&list);
	return (res);
}

int main()
{
	int fd;
	
	fd = open("59text.txt", O_RDONLY);

	printf("test1 :%s\n", get_next_line(fd));
	printf("test2 :%s\n", get_next_line(fd));
	printf("test3 :%s\n", get_next_line(fd));
	printf("test4 :%s\n", get_next_line(fd));
	close (fd);
	return(0);
}