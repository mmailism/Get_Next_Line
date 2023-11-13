#include "get_next_line.h"

void	ft_swipe_list(t_list **list)
{
	t_list	*last_node;
	t_list	*clean_node;
	int		i;
	int		k;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (buf == NULL || clean_node == NULL)
		return ;
	last_node = ft_find_last_node(*list);

	i = 0;
	k = 0;
	while (last_node->str_buf[i] != '\0' && last_node->str_buf[i] != '\n')
		i++;
	while (last_node->str_buf[i] != '\0' && last_node->str_buf[++i])
		buf[++k] = last_node->str_buf[i];
	buf[k] = '\0';
	clean_node->str_buf = buf;
	clean_node->next = NULL;
	dealloc(list, clean_node, buf);
}

void	ft_merge(t_list **list, char *buf)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = ft_find_last_node(*list);
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	//if list empty
	//if NULL == *list
	if (last_node == NULL)
		*list = new_node;
	else
		last_node->next = new_node;

	new_node->str_buf = buf;
	new_node->next = NULL;
}

void	ft_create_list(t_list **list, int fd)
{
	int		char_read;
	char	*buf;

	//scan line if '\n' present
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

char	*ft_get_line(t_list *list)
{
	int		str_len;
	char	*next_str;

	if (list == NULL)
		return (NULL);
	//Count char till '\n' So know how much to malloc
	str_len = ft_len_newline(list);
	next_str = malloc(str_len + 1);
	if (next_str == NULL)
		return (NULL);

	//Copy string in buffer and return
	ft_copy_str(list, next_str);
	return (next_str);
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*next_line;
	//fd only positive | read -1 if some problems on reading
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0 < 0))
		return (NULL);
	//Create list till i stumble into '\n'
	ft_create_list(&list, fd);

	if (list == NULL)
		return (NULL);
	//fetch line from list
	next_line = ft_get_line(list);
	//
	ft_swipe_list(&list);
	return (next_line);
}

int	main()
{
	int		fd;
	char	*line;
	int		line_s;

	line_s = 1;
	fd = open("file.txt", O_RDONLY);
	while (line == get_next_line(fd))
		printf("%d->%s\n", line_s++, line);
}
