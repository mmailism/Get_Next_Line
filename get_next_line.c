/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maramick <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:13:01 by kpueankl          #+#    #+#             */
/*   Updated: 2024/01/25 14:30:07 by maramick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	set_zero(char *ptr, int size)
{
	int	i;

	i = 0;
	while (i != size)
	{
		ptr[i] = 0;
		i++;
	}
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
		if (list)
			free(list);
		list = NULL;
		return (NULL);
	}
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		if (list)
			free(list);
		list = NULL;
		return (NULL);
	}
	set_zero(buffer, BUFFER_SIZE + 1);
	line = read_line(fd, buffer, &list);
	free(buffer);
	if (!line)
	{
		if (list)
			free(list);
		list = NULL;
		return ( NULL);
	}
	list = get_list(line);
	new_line = get_newline(line);
	if (!new_line)
	{
		if (list)
			free(list);
		list = NULL;
	}
	free(line);
	return (new_line);
}

char	*read_line(int fd, char *buffer, char **addr_list)
{
	int		rd;
	char	*tmp;
	char	*list;

	list = *addr_list;
	rd = 1;
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

// char	*get_list(char *list)
// {
// 	int		i;
// 	char	*tmp;
// 	char	mem;

// 	i = 0;
// 	mem = ft_strlen(list, 1);
// 	if (mem == 0)
// 		return (NULL);
// 	tmp = (char *)malloc(mem + 1);
// 	if (!tmp)
// 		return (NULL);
// 	while (list[i] != '\0' && list[i] != '\n')
// 	{
// 		tmp[i] = list[i];
// 		i++;
// 	}
// 	if (list[i] == '\n')
// 		tmp[i++] = '\n';
// 	tmp[i] = '\0';
// 	tmp = ft_substr(list, i + 1, ft_strlen(list, 1) - 1);
// 	if (!tmp)
// 		return (free(tmp), NULL);
// 	return (tmp);
// }

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
