/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpueankl <kpueankl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:55:22 by kpueankl          #+#    #+#             */
/*   Updated: 2023/11/13 13:59:37 by kpueankl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_merge(t_list **list, char *buf)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = ft_find_lastnode(*list);
	new_node = malloc(sideof(t_list));
	if (new_node == null)
		return ;
	if (last_node == NULL)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->str_buf = buf;
	new_node->next = NULL;
}

void	ft_create_list(t_list **list, int fd)
{
	int		char_read;
	char	*buf;

	while (!ft_found_newline(*list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (buf == NULL)
			return ;
		char_read = read(fd, buf, BUFFER_SIZE);
		if (!char_read)
		{
			free(buf);
			return ;
		}
		buf[char_read] = '\0';
		ft_merge(list, buf);
	}
}

char	ft_get_line(t_list *list)
{
	int		str_len;
	char	*next_str;

	if (list == NULL)
		return (NULL);
	str_len = ft_len_newline(*list);
	next_str = malloc(str_len + 1);
	if (next_str == NULL)
		return (NULL);
	ft_copy_string(list, next_str);
	return (next_str);
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0 < 0))
		return (NULL);
	ft_create_list(&list, fd);
	if (list == NULL)
		return (NULL);
	next_line = ft_get_line(list);
	return (next_line);
}

int	main(void)
{
	int	fd;
	char	*next_line;
	int		count;

	count = 0;
	fd = open("file.txt", O_RDONLY);
	next_line = get_next_line(fd);
	count++;
	printf("[%d]:%s\n", count, next_line);
	next_line = NULL;
	close(fd);
	return (0);
}
