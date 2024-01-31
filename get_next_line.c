/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammai <iammai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:13:01 by kpueankl          #+#    #+#             */
/*   Updated: 2024/01/31 14:48:33 by iammai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*	gnl has function "read_line" "get_list" "get_newline" 
	**read_line is function read(fd, buffer, BUFFER_SIZE)
	**get_list is function cut string by substr
	**get_newline is function malloc all string and return
		free(), set NULL and output */

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

/*	function read_line read everything put in list
	but string is newline put in list dosen't in while roop
	and combine list and buffer of function read */

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

/*	function get_list is cut string at point not null not newline
	use ft_substr malloc string */

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

/*	function get_newline is function malloc all string return*/

char	*get_newline(char *str)
{
	int		i;
	int		byte;
	char	*new_line;

	i = 0;
	byte = ft_strlen(str, 1);
	if (byte == 0)
		return (NULL);
	new_line = (char *)malloc(byte + 1);
	if (!new_line)
		return (NULL);
	while (str[i])
	{
		new_line[i] = str[i];
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

/* function set_zero mem 1 set buffer = 0 || mem 2 free pointer and set NULL */

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
