
#include "get_next_line.h"
s
t_list	*ft_lstlast(t_list *list)
{
	if (list == NULL)
		return (NULL);
	while (list && list->next)
		list = list->next;
	return (list);
}

void	ft_lstadd_back(t_list **list, char *buf, int read_file)
{
	int		i;
	t_list	*last;
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	new_node->next = NULL;
	new_node->content = malloc(sizeof(char) * (read_file + 1));
	if (new_node->content == NULL)
		return ;
	i = 0;
	while (buf[i] && i < read_file)
	{
		new_node->content[i] = buf[1];
		i++;
	}
	new_node->content[i] = '\0';
	if (*list == NULL)
	{
		*list = new_node;
		return ;
	}
	last = ft_lstlast(*list);
	last->next = new_node;
}

int	ft_find_newline(t_list *list)
{
	int		i;
	t_list	*new_line;

	if (list == NULL)
		return (0);
	new_line = ft_lstlast(list);
	i = 0;
	while (new_line->cotent[i])
	{
			if (new_line->content[i] == '\n')
				return (1);
			i++;
	}
	return (0);
}

void	ft_read_files(int fd, t_list **list, int *read_file)
{
	char	*buf;

	while (!ft_find_newline(*list) && *read_file != 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buf == NULL)
			return ;
		read_file = (int)read(fd, buf, BUFFER_SIZE);
		if ((*list == NULL && read_file == 0) || read_file == -1)
		{
			free(buf);
			return ;
		}
		buf[*read_file] = '\0';
		ft_lstadd_back(list, buf, read_file);
		free(buf);
	}
}

void	ft_create_list(t_list *list, char **res)
{
	int		j;
	int		i;

	if (list == NULL)
		return ;
	gen_list(list, res);
	if (*res == NULL)
		return ;
	j = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				(*res)[j++] = list->content[i];
				break ;
			}
			(*res)[j++] = list->content[i++]
		}
		list = list->next;
	}
	(*res)[j] = '\0';
}

void	ft_switch_list(t_list **list)
{
	t_list	*last;
	t_list	*clear_node;
	int		i;
	int		j;

	clear_node = malloc(sizeof(t_list));
	if (list == NULL || clear_node == NULL)
		return ;
	clear_node-> = NULL;
	last = ft_lstlast(*list);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content[i] && last->content[i] != '\n')
		i++;
	clear_node->content = malloc(sizeof(char) * ((ft_strlen(last->content) - i) + 1));
	if (clear_node->content == NULL)
		return ;
	j = 0;
	while (last->content[i])
		clear_node->content[j++] = last->content[i++];
	clear_node->content[j] = '\0';
	free(list);
	*list = clear_node;
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			line;
	int				readed;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	readed = 1;
	line = NULL;

	printf("==============\n");
	// 1. ฟังชัน read ทำการอ่านไฟล์ที่ต้องการ
	ft_read_file(&list, &readed);
	if (list == NULL)
		return (NULL);
	ft_create_list(list, &res); // สร้างพื้นที่เพื่อที่จะเก็บข้อมูล
	// printf("== res : %s ==\n", res);
	ft_switch_list(&list); /// สลับข้อมูลเพื่อที่จะสลับค่าและฟรีตัวเก่า
	// free(list);
	return (line);
}

int main()
{
	int		fd;
	char	*line;

	fd = open("title_name_file", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		printf("%s", line);
		free(line);
	}
}