#include "get_next_line.h"

t_list	*ft_last_node(t_list *str_buf)
{
	if (str_buf == NULL)
		return (NULL);
	while (str_buf->next)
		str_buf = str_buf->next;
	return (str_buf);
}

void	ft_merge(t_list **str_buf, char *buf)
{
	t_list	*new_node;
	t_list	*next_node;

	next_node = ft_last_node(*str_buf);
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	if (next_node == NULL)
		*str_buf = new_node;
	else
		next_node->next = new_node;
	
	new_node->list = buf;
	next_node->next = '\0';
}

int	ft_find_newline(t_list *str_buf)
{
	int	i;

	if (str_buf == NULL)
		return (0);
	while (str_buf)
	{
		i = 0;
		while (str_buf->list[i] && i < BUFFER_SIZE)
		{
			if (str_buf->list[i] == '\n')
				return (i);
			i++;
		}
		str_buf = str_buf->next;
	}
	return (0);
}

char	ft_create_list(t_list **str_buf, int fd)
{
	char	*buf;
	int		read_char;

	while (!ft_find_newline(*str_buf))
	{
		buf = malloc(BUFFER_SIZE + 1);
		read_char = read(fd, buf, BUFFER_SIZE);
		if (!read_char)
		{
			free(buf);
		}
		buf[read_char] = '\0';
		ft_merge(str_buf, buf);
		printf("test s : %s\n test_read : %d\n", s, read_char);
	}
	return (buf);
}

char	*get_next_line(int fd)
{
	static t_list	*str_buf = NULL;
	char			result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ft_create_list(&str_buf, fd);

	if (str_buf == NULL)
		return (NULL);
	ft_getline
}

int	main(void)
{
	int	fd = 1;

	printf("==main==%s", get_next_line(fd));
	return(0);
}
