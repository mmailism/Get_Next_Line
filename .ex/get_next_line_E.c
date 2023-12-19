/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_E.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammai <iammai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:13:01 by kpueankl          #+#    #+#             */
/*   Updated: 2023/12/19 15:35:43 by iammai           ###   ########.fr       */
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

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*res;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		// if (fd > 0 && list)
		// 	ft_lstclear(&list, free);
		return (NULL);
	}
	ft_read_list(&list, fd);
	if (!list)
		return (NULL);
	ft_create_list(list, &res);
	ft_re_list(&list);
	return (res);
}

void	ft_re_list(t_list **list)
{
	t_list	*lst_ls;
	t_list	*new_n;
	char	*content;
	int		i;
	int		j;

	i = 0;
	lst_ls = ft_lstlast(*list);
	if (!lst_ls)
		return ;
	content = lst_ls->content;
	i = lst_ls->len;
	lst_ls->content = NULL;
	ft_lstclear(list, free);
	if (content[i] != '\0')
	{
		i = 0;
		while (content[i] != '\0')
			content[j++] = content[i++];
		content[j] = '\0';
		new_n = ft_lstnew(content);
		ft_lstadd_back(list, new_n);
	}
	else
		free(content);
}

void	ft_create_list(t_list *list, char **res)
{
	t_list	*lst_s;
	int		len_n;
	int		i;

	lst_s = list;
	len_n = 0;
	while (lst_s)
	{
		len_n = len_n + lst_s->len;
		lst_s = lst_s->next;
	}
	if (!len_n)
		return ;
	*res = malloc(sizeof(**res) * (len_n + 1));
	if (!res)
		return ;
	len_n = 0;
	while (list && list->content)
	{
		i = 0;
		while (list->content[i] && i < list->len)
			(*res)[len_n++] = list->content[i++];
		list = list->next;
	}
	(*res)[len_n] = '\0';
}

void	ft_read_list(t_list **list, int fd)
{
	t_list	*new_n;
	int		read_lst;
	char	*buf;
	
	read_lst = 1;
	while (!found_newline(*list))
	{
		buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
		new_n = ft_lstnew(buf);
		new_n->content = (char *)malloc(sizeof(buf) * BUFFER_SIZE + 1);
		read_lst = read(fd, new_n->content, BUFFER_SIZE);
		if (read_lst == -1)
		{
			free(new_n->content);
			free(new_n);
			free(buf);
			break ;
		}
		new_n->content[BUFFER_SIZE] = '\0';
		ft_lstadd_back(list, new_n);
	}
}

int	found_newline(t_list *list)
{
	int		i;
	
	i = 0;
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

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*i;
	size_t			j;

	i = s;
	j = 0;
	if (n == 0)
		return ;
	while (j < n)
	{
		i[j] = 0;
		j++;
	}
}

int main()
{
	int fd;
	
	fd = open("43_with_nl.txt", O_RDONLY);

	printf("-- out 1 : %s --\n", get_next_line(fd));
	printf("-- out 2 : %s --\n", get_next_line(fd));
	printf("-- out 3 : %s --\n", get_next_line(fd));
	printf("-- out 4 : %s --\n", get_next_line(fd));
	printf("============================\n");
	close (fd);
	return(0);
}
