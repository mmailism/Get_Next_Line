/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mai <Mai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:13:01 by kpueankl          #+#    #+#             */
/*   Updated: 2024/01/25 16:45:09 by Mai              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*set_zero(char *ptr, size_t mem)
{
	int	i;
	int	size;

	size = BUFFER_SIZE + 1;
	i = 0;
	if (mem == 1)
	{
		while (i != size)
		{
			ptr[i] = 0;
			i++;
		}
	}
	else if (mem == 2)
	{
		if (ptr != NULL)
			free(ptr);
		ptr = NULL;
	}
	return (NULL);
}

size_t	ft_strlen(char *str, size_t mem)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	if (mem == 1)
	{
		while (str[i] != '\0')
			i++;
	}
	else if (mem == 2)
	{
		if (str[0] == '\0')
			return (0);
		while (str[i] != '\0' && str[i] != '\n')
			i++;
		if (str[i] == '\n')
			i++;
	}
	return (i);
}

char	*get_next_line(int fd)
{
	static char	*list = NULL;
	char		*buffer;
	char		*line;
	char		*new_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		list = set_zero(list, 2);
		return (NULL);
	}
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		list = set_zero(list, 2);
		return (NULL);
	}
	line = read_line(fd, buffer, &list, 1);
	free(buffer);
	if (!line)
		return (set_zero(list, 2));
	list = get_list(line);
	new_line = get_newline(line);
	if (!new_line)
		list = set_zero(list, 2);
	return (free(line), new_line);
}

char	*read_line(int fd, char *buffer, char **addr_list, int rd)
{
	char	*tmp;
	char	*list;

	set_zero(buffer, 1);
	list = *addr_list;
	while (!(ft_strchr(list, '\n')))
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd == -1)
			return (NULL);
		else if (rd == 0)
			break ;
		buffer[rd] = 0;
		if (!list)
			list = ft_strdup("");
		tmp = list;
		list = ft_strjoin(tmp, buffer);
		if (!list)
		{
			*addr_list = NULL;
			return (NULL);
		}
		free(tmp);
	}
	return (list);
}

char	*get_list(char *list)
{
	int		i;
	char	*tmp;

	i = 0;
	while (list[i] != '\0' && list[i] != '\n')
		i++;
	if (list[i] == '\0')
		return (NULL);
	tmp = ft_substr(list, i + 1, ft_strlen(list, 1) - 1);
	if (!tmp)
		return (NULL);
	if (tmp[0] == '\0')
	{
		free(tmp);
		tmp = NULL;
		return (NULL);
	}
	list[i + 1] = '\0';
	return (tmp);
}
