#include "get_next_line.h"

char	ft_switch_line(t_list *list_line)
{ // switch front to keep
	t_list	*last_node;
	t_list	*clear_node;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	clear_node = malloc(sizeof(t_list));
	if (buf == NULL || clear_node == NULL)
		return ;
}

int	ft_len_newline(t_list *list_line)
{
	int	i;
	int	len;

	if (list_line == NULL)
		return (0);
	len = 0;
	while (list_line)
	{
		i = 0;
		while (list_line->list[i])
		{
			if (list_line->list[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			++len;
		}
		list_line = list_line->next;
	}
	return (len);
}

char	*ft_get_line(t_list *list_line)
{
	int		str_len;
	char	*next_str;
	int		i;
	int		k;
	char	*str;

	if (list_line == NULL)
		return (NULL);
	
	str_len = ft_len_newline(list_line); //count \n how much
	next_str = malloc(str_len + 1);
	if (next_str == NULL)
		return (NULL);

	k = 0;
	while (list_line)
	{
		i = 0;
		while (list_line->list[i])
		{
			if (list_line->list[i]== '\n')
			{
				str[k++] = '\n';
				str[k] = '\0';
				return ;
			}
			str[k] = list_line->list[++i];
		}
		list_line = list->next;
	}
	str[k] = '\0';
}

char	ft_add_list(t_list *list_line, int fd)
{
	int		read_char;
	char	*buf;
	t_list	*new_node;
	t_list	*last_node;

	while (!ft_find_newline(*list_line)) //check newline
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (buf == NULL)
			return ;
		
		read_char = read(fd, buf, BUFFER_SIZE);

		if (!read_char)
		{
			free(buf); //free malloc
			return ;
		}
		buf[read_char] = '\0';
		new_node = malloc(sizeof(t_list));
		if (new_node == NULL)
			return ;
		if (last_node == NULL)
			*list_line = new_node;
		else
			last_node->next = new_node;

		new_node->list = buf;
		new_node->next = NULL;
	}	
}

char	*get_next_line(int fd)
{
	static t_list	*list_line = NULL;
	char			*result;

	if (fd <= 0 || BUFFER_SIZE <= 0|| read(fd, &result, 0 < 0))
		return (NULL);
	ft_add_list(&list_line, fd); // funtion add list and read 

	if (list_line == NULL)
		return (NULL);
	next_line = ft_get_line(list_line); // find nextline and create newline

	ft_switch_list(&list_line); // switch for keep
	return (result);
}

int	main(void)
{
	int		fd;
	char	*line;
	int		line_s;

	line_s = 1;
	fd = open("file.txt", O_RDONLY);

	while (line == get_next_line(fd))
		printf("%d->%s\n", line_s++, line);
}
