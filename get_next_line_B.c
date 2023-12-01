
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

void	ft_lstadd_back(t_list **list, t_list *new)
{
	t_list	*temp;

	if (!list || !new)
		return ;
	if (!(*list))
	{
		*list = new;
		return ;
	}
	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
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

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return ;
	while (!ft_find_newline(*list) && *read != 0)
	{
		read_file = (int)read(fd, buf, BUFFER_SIZE);
		if ((*list == NULL && read_file == 0) || read_file == -1)
		{
			free(buf);
			return ;
		}
		buf[*read_file] = '\0';
		ft_lstadd_back(list, read_file);
	}
}

void	ft_create_list(t_list *list, char **readed)
{
	int		len;
	int		i;
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	new_node->next = NULL;
	new_node->content = malloc(sizeof(char) * (readed + 1));
	if (new_node->content == NULL)
		return ;
	i = 0;
	while (buf[i] && i < readed)
	{
		new_node->content[i] = buf[i];
		while (list->content[i])
			(*res)[len++] = list->content[i++];
		list = list->next;
	}
	printf("len : %d\n", len);
}

void	ft_switch_list()
{

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