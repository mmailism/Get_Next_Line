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
