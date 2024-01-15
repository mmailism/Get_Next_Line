#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
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

char	*read_line(int fd, char *buffer, t_list *list)
{
	t_list	node_n;
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
		list->content = ft_strjoin(tmp, buffer);
		if (!list->content)
			return (NULL);
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
			tmp[i++] = list[i++];
		while (buffer[j] != '\0')
			tmp[i++] = buffer[j++];
		tmp[i] = '\0';
	}
	free(list);
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
		return (NULL);
	return (tmp);
}
