/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpueankl <kpueankl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:13:01 by kpueankl          #+#    #+#             */
/*   Updated: 2024/01/05 15:56:18 by kpueankl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	find_line_ending(char *str, size_t i)
{
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

char	*get_string(char *str)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (str[i] == '\0')
		return (free(str), NULL);
	i = find_line_ending(str, i);
	new_str = (char *)malloc((ft_strlen(str) - i + 1));
	if (!new_str)
		return (free(new_str), NULL);
	while (str[i])
		new_str[j++] = str[i++];
	new_str[j] = '\0';
	if (!new_str[0])
		return (free(str), free(new_str), NULL);
	free(str);
	return (new_str);
}

char	*read_the_line(char *str)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (NULL);
	i = find_line_ending(str, i);
	line = (char *)malloc(sizeof(char) * i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*free_and_null(char *buff1, char *buff2)
{
	free(buff1);
	free(buff2);
	buff2 = NULL;
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*read_buffer;
	char		*read_content;
	int			read_bytes;

	read_bytes = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	read_content = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!read_content)
		return (NULL);
	while (!(ft_strchr(read_buffer, '\n')) && read_bytes != 0)
	{
		read_bytes = read(fd, read_content, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			read_buffer = free_and_null(read_content, read_buffer);
			return (NULL);
		}
		read_content[read_bytes] = '\0';
		read_buffer = ft_strjoin(read_buffer, read_content);
	}
	free(read_content);
	read_content = read_the_line(read_buffer);
	read_buffer = get_string(read_buffer);
	return (read_content);
}
