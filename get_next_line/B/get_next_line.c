/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpueankl <kpueankl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:13:01 by kpueankl          #+#    #+#             */
/*   Updated: 2024/01/05 15:45:21 by kpueankl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//!now ft_read_file

void	*ft_read_file(int fd, t_list **list)
{
	char	*buf;
	int		read_file;

	while (!ft_find_newline(*list) && read_file != 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buf == NULL)
			return ;
		read_file = read(fd, buf, BUFFER_SIZE);
		if ((*list == NULL && read_file == 0) || read_file == -1)
		{
			free(buf);
			return ;
		}
		buf[read_file] = '\0';
		ft_lstadd_back(list, buf);
		free(buf);
	}
}

void	ft_add_list(t_list *list, char **line)
{
	int	i;
	int	len;

	len = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		list = list->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
}

void	ft_create_list(t_list *list, char *line)
{
	int		j;
	int		i;

	if (list == NULL)
		return ;
	ft_add_list(list, line);
	if (*line == NULL)
		return ;
	j = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				(*line)[j++] = list->content[i];
				break ;
			}
			(*line)[j++] = list->content[i++];
		}
		list = list->next;
	}
	(*line)[j] = '\0';
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

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*line;
	int				read_file;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	read_file = 1;
	line = NULL;

	ft_read_file(&list, &read_file);
	if (list == NULL)
		return (NULL);
	ft_create_list(list, &line);
	ft_switch_list(&list);
	if (line[0] == '\0')
	{
		ft_free_list(list);
		list = NULL;
		free(line);
		return (NULL)
	}
	return (line);
}
