#include "get_next_line.h"

void	create_list(t_list **list, int fd)
{

	int		char_read;
	char	*buf;

	//scan line if '\n' present
	while (!found_newline(*list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (NULL == buf)
			return ;
									//10
		char_read = read(fd, buf, BUFFER_SIZE);
		//		EOF
		if (!char_read)
		{
			free(buf);
			return ;
		}
		buf[char_read] = '\0';
		// Append the node
		append(list, buf);
	}

}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*next_line;
	//fd only positive | read -1 if some problems on reading
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0 < 0))
		return (NULL);
	//Create list till i stumble into '\n'
	create_list(&list, fd);

	if (list == NULL)
		return (NULL);
	//fetch line from list
	next_line = get_next_line(list);
	//
	polish_list(&list);
	return (next_line);
}
