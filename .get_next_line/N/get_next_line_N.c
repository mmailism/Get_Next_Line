/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_N.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammai <iammai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:13:01 by kpueankl          #+#    #+#             */
/*   Updated: 2024/01/08 16:32:23 by iammai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(int fd, char *buf, char *backup)
{
	int		check;
	char	*temp;

	check = 1;
	while (check)
	{
		check = read(fd, buf, BUFFER_SIZE);
		if (check == -1)
			return (0);
		else if (check == 0)
			break ;
		buf[check] = '\0';
		if (!backup)
			backup = ft_strdup("");
		temp = backup;
		backup = (ft_strjoin(temp, buf));
		if (!backup)
			return (NULL);
		free (temp);
		temp = NULL;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (backup);
}

static char	*extract(char *line)
{
	int		i;
	char	*temp;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0')
		return (NULL);
	temp = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (!temp)
		return (NULL);
	if (temp[0] == '\0')
	{
		free (temp);
		temp = NULL;
		return (NULL);
	}
	line[i + 1] = '\0';
	return (temp);
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	static char	*backup;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	line = read_line(fd, buf, backup);
	free(buf);
	if (!line)
		return (NULL);
	backup = extract(line);
	return (line);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*temp;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	temp = malloc(len + 1);
	if (!temp)
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
			temp[j++] = s[i];
		i++;
	}
	temp[j] = '\0';
	return (temp);
}

char	*ft_strdup(const char *s1)
{
	char	*temp;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (s1[i])
	{
		len++;
		i++;
	}
	temp = (char *)malloc(sizeof(char) * len + 1);
	if (!temp)
		return (0);
	i = 0;
	while (i < len)
	{
		temp[i] = s1[i];
		i++;
	}
	temp[i] = 0;
	return (temp);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	temp = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!temp)
		return (NULL);
	while (s1[j])
		temp[i++] = s1[j++];
	j = 0;
	while (s2[j])
		temp[i++] = s2[j++];
	temp[i] = '\0';
	return (temp);
}

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	temp;

	i = 0;
	temp = (unsigned char) c;
	while (s[i])
	{
		if (s[i] == temp)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == temp)
		return ((char *)s + i);
	return (NULL);
}

#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int	fd;
	char	*line;

	fd = open("43_with_nl.txt", O_RDONLY);

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return 0;
}