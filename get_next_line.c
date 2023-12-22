/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammai <iammai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:13:01 by kpueankl          #+#    #+#             */
/*   Updated: 2023/12/22 19:44:44 by iammai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*line = NULL;
	char			*res;
	char			*buf;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	ft_read(line, fd, buf);
	if (!line)
		return (NULL);
	ft_create(line, res);
	ft_re_list(line);
	// if (!line)
	// {
	// 	free_stash(line);
	// 	line = NULL;
	// 	free(res);
	// 	return (NULL);
	// }
	return (res);
}

t_list	*ft_re_list(t_list *line)
{
	t_list	*last;
	t_list	*clear_node;
	int		i;

	clear_node = malloc(sizeof(t_list));
	if (line == NULL || clear_node == NULL)
	{
		line = clear_node;
		return (NULL);
	}
	clear_node->next = NULL;
	last = ft_lstlast(line);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content[i] == '\n')
		i++;
	clear_node->content = trim_last_list_element_helper(last, i);
	if (clear_node->content == NULL)
		return (NULL);
	free_stash(line);
	line = clear_node;
	return (clear_node);
}

t_list	*ft_create(t_list *line, char *res)
{
	int	i;
	int	j;

	if (!line)
		return (NULL);
	generate_line(line, res);
	if (!res)
		return (NULL);
	j = 0;
	while (line)
	{
		i = 0;
		while (line->content[i])
		{
			if (line->content[i] == '\n')
			{
				res[j++] = line->content[i++];
				break ;
			}
			res[j++] = line->content[i++];
		}
		line = line->next;
	}
	res[j] = '\0';
	return (line);
}

t_list	*ft_read(t_list *line, int fd, char *buf)
{
	int		read_list;
	
	read_list = 1;
	while (!found_newline(line) && read_list != 0)
	{
		if (!buf)
			return (NULL);
		read_list = read(fd, buf, BUFFER_SIZE);
		if (line == NULL || read_list == 0 || read_list == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[read_list] = '\0';
		add_join_next(line, buf, read_list);
	}
	free(buf);
}

int	found_newline(t_list *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line->next != 0)
		line = line->next;
	while (line->content[i])
	{
		if (line->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int main()
{
	int fd;
	char	*i;

	fd = open("1char.txt", O_RDONLY);
	i = get_next_line(fd);

	printf("-- out 1 : %s --\n", i);
	free(i);
	i = get_next_line(fd);
	printf("-- out 2 : %s --\n", i);
	free(i);
	close (fd);
	return(0);
}
