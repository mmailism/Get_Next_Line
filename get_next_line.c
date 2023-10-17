#include "get_next_line.h"

void	ft_create_list(t_list **list, int fd)
{
	int		char_read;
	char	*buf;

	while (!ft_found_newline(*list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (buf == NULL)
			return ;

		char_read = read(fd, buf, BUFFER_SIZE);

		if (!char_read)
		{
			free(buf);
			return ;
		}
		buf[char_read] = '\0';
		ft_merge(list, buf);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0 < 0))
		return (NULL);

	ft_create_list(&list, fd);

	if (list == NULL)
		return (NULL);

	next_line = ft_get_line(list);

	ft_swipe_list(&list);
	return (next_line);
}
