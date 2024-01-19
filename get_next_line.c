/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mai <Mai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:13:01 by kpueankl          #+#    #+#             */
/*   Updated: 2024/01/19 13:33:35 by Mai              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	set_zero(char *ptr, int size)
{
	int	i;

	i = 0;
	while (i != size)
	{
		ptr[i] = 0;
		i++;
	}
}

char	*get_next_line(int fd)
{
	static char	*list = NULL;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (list)
			free(list);
		list = NULL;
		return (NULL);
	}
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	set_zero(buffer, BUFFER_SIZE + 1);
	line = read_line(fd, buffer, list);
	free(buffer);
	if (!line)
		return (free(list), NULL);
	list = get_list(line);
	return (line);
}

char	*read_line(int fd, char *buffer, char *list)
{
	int		rd;
	char	*tmp;

	rd = 1;
	while (!(ft_strchr(list, '\n')))
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd == -1)
			return (free(buffer), NULL);
		else if (rd == 0)
			break ;
		buffer[rd] = 0;
		if (!list)
			list = ft_strdup("");
		tmp = list;
		list = (ft_strjoin(tmp, buffer));
		if (!list)
			return (NULL);
		free(tmp);
	}
	return (list);
}

void	*get_list(char *list)
{
	int		i;
	char	*tmp;

	i = 0;
	while (list[i] != '\0' && list[i] != '\n')
		i++;
	if (list[i] == '\0')
		return (NULL);
	tmp = ft_substr(list, i + 1, ft_strlen(list) - 1);
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

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (*str != '\0')
	{
		str++;
		i++;
	}
	return (i);
}

/*Buffer Overflow becuase didn't check *s*/
char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	if (c == '\0')
	{
		while (*s != '\0')
			s++;
		return ((char *)s);
	}
	while (*s != (char)c)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}

// #include <fcntl.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int	fd;
// 	char	*line;

// 	fd = open("read_error.txt", O_RDONLY);

// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s\n", line);
// 		free(line);
// 	}
// 	close(fd);
// 	fd = open("43_with_nl.txt", O_RDONLY);

// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s\n", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return 0;
// }
