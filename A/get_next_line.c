#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*list = NULL;
	char			*buffer;
	char			*line;

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
	while (list)
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
		list = ft_strjoin(tmp, buffer);
		if (!list)
			return (NULL);
		if (!count_list(list, buffer))
			break ;
		free(tmp);
	}
	// free(buffer);
	return (list);
}

char	*ft_strjoin(char *list, char *buffer)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = 0;
	j = 0;
	if (!list || !buffer)
		return (NULL);
	tmp = count_list(list, buffer);
	if (tmp != NULL)
	{
		while (list[i] != '\0')
		{
			tmp[i] = list[i];
			i++;
		}
		while (buffer[j] != '\0')
			tmp[i++] = buffer[j++];
		tmp[i] = '\0';
	}
	// free(list);
	return (tmp);
}

char	*count_list(char *list, char *buffer)
{
	size_t	i;
	size_t	cnt_list;
	size_t	cnt_buffer;
	char	*tmp;
	i = 0;
	if (list)
	{
		if (buffer[0] == '\0')
			return (NULL);
		while (buffer[i] != '\0')
		{
			if (buffer[i] == '\n')
				return (NULL);
			i++;
		}
		return (buffer);
	}
	cnt_list = ft_strlen(list);
	cnt_buffer = ft_strlen(buffer);
	tmp = (char *)malloc(cnt_list + cnt_buffer + 1);
	if (!tmp)
		return (free(tmp), NULL);
	return (tmp);
}

size_t	ft_strlen(char const *str)
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	tmp = malloc(len + 1);
	if (!tmp)
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
			tmp[j++] = s[i];
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	s_len;
	size_t	i;

	i = 0;
	s_len = ft_strlen(s);
	dup = (char *)malloc((s_len * sizeof(char)) + 1);
	if (dup == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int	fd;
	char	*line;

	fd = open("read_error.txt", O_RDONLY);

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	fd = open("43_with_nl.txt", O_RDONLY);

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return 0;
}
