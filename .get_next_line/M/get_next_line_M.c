#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*read_buf;
	char		*content;
	int			read_bytes;

	read_bytes = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	content = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!content)
		return (NULL);
	while (!(ft_strchr(read_buf, '\n')) && read_bytes != 0)
	{
		read_bytes = read(fd, content, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			read_buf = free_and_null(content, read_buf);
			return (NULL);
		}
		content[read_bytes] = '\0';
		read_buf = ft_strjoin(read_buf, content);
	}
	free(content);
	content = create_list(read_buf);
	read_buf = get_list(read_buf);
	return (content);
}

char *create_list(char *read_buf)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!read_buf || read_buf[0] == '\0')
		return (NULL);
	i = find_lastline(read_buf, i);
	line = (char *)malloc(sizeof(char) * i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (read_buf[i] && read_buf[i] != '\n')
	{
		line[i] = read_buf[i];
		i++;
	}
	if (read_buf[i] == '\n')
	{
		line[i] = read_buf[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_list(char *read_buf)
{
	char	*str_n;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (read_buf[i] == '\0')
		return (free(read_buf), NULL);
	i = find_lastline(read_buf, i);
	str_n = (char *)malloc(ft_strlen(read_buf) - i + 1);
	if (!str_n)
		return (free(str_n), NULL);
	while (read_buf[i])
		str_n[j++] = read_buf[i++];
	str_n[j] = '\0';
	if (!str_n[0])
	{
		free_and_null(read_buf, str_n);
		return (NULL);
	}
	free(read_buf);
	return (str_n);
}

char	*ft_strdup(const char *s)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = ft_strlen(s);
	str = (char *)malloc(sizeof(*str) * (j + 1));
	if (!str)
		return (NULL);
	while (i < j)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char *buffer, char *content)
{
	size_t	i;
	size_t	j;
	char	*result;

	if (!buffer)
		return (ft_strdup(content));
	if (!content)
		return (ft_strdup(buffer));
	i = 0;
	result = (char *)malloc(sizeof(char) * (ft_strlen(buffer)
				+ ft_strlen(content)) + 1);
	if (!result)
		return (NULL);
	while (buffer && buffer[i])
	{
		result[i] = buffer[i];
		i++;
	}
	j = 0;
	while (content && content[j])
		result[i++] = content[j++];
	result[i] = '\0';
	free(buffer);
	return (result);
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

char	*free_and_null(char *buff1, char *buff2)
{
	free(buff1);
	free(buff2);
	buff2 = NULL;
	return (0);
}

char	*ft_strchr(const char *s, int c)
{
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

size_t	find_lastline(char *read_buf, size_t i)
{
	while (read_buf[i] && read_buf[i] != '\n')
		i++;
	if (read_buf[i] == '\n')
		i++;
	return (i);
}

int main()
{
	int fd;
	
	fd = open("43_with_nl.txt", O_RDONLY);

	printf("-- out 1 : %s --\n", get_next_line(fd));
	printf("-- out 2 : %s --\n", get_next_line(fd));
	printf("-- out 3 : %s --\n", get_next_line(fd));
	printf("-- out 4 : %s --\n", get_next_line(fd));
	printf("============================\n");
	close (fd);
	return(0);
}
