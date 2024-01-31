#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*str;

	fd = open("multiple_nl.txt", O_RDONLY);
	if (fd < 0)
		return (0);
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
	// str = get_next_line(fd);
	// printf("%s", str);
	// free(str);
	// str = get_next_line(fd);
	// printf("%s", str);
	// free(str);
	// str = get_next_line(fd);
	// printf("%s", str);
	// free(str);

	// close(fd);

	// fd = open("multiple_nl.txt", O_RDONLY);
	// if (fd < 0)
	// 	return (0);
	// str = get_next_line(fd);
	// printf("%s", str);
	// free(str);
	// str = get_next_line(fd);
	// printf("%s", str);
	// free(str);
	// str = get_next_line(fd);
	// printf("%s", str);
	// free(str);
}