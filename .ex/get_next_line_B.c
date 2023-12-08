
// #include "get_next_line.h"

// t_list	*ft_lstlast(t_list *list)
// {
// 	if (list == NULL)
// 		return (NULL);
// 	while (list && list->next)
// 		list = list->next;
// 	return (list);
// }

// void	ft_lstadd_back(t_list **list, char *buf, int read_file) // !next fix
// {
// 	int		i;
// 	t_list	*last;
// 	t_list	*new_node;

// 	new_node = malloc(sizeof(t_list));
// 	if (new_node == NULL)
// 		return ;
// 	new_node->next = NULL;
// 	new_node->content = malloc(sizeof(char) * (read_file + 1));
// 	if (new_node->content == NULL)
// 		return ;
// 	i = 0;
// 	while (buf[i] && i < read_file)
// 	{
// 		new_node->content[i] = buf[1];
// 		i++;
// 	}
// 	new_node->content[i] = '\0';
// 	if (*list == NULL)
// 	{
// 		*list = new_node;
// 		return ;
// 	}
// 	last = ft_lstlast(*list);
// 	last->next = new_node;
// }

// void	ft_free_list(t_list *list)
// {
// 	t_list	*curr;
// 	t_list	*next;

// 	curr = list;
// 	while (curr)
// 	{
// 		free(curr->content);
// 		next = curr->next;
// 		free(curr);
// 		curr = next;
// 	}
// }

// int	ft_find_newline(t_list *list)
// {
// 	int		i;
// 	t_list	*new_line;

// 	if (list == NULL)
// 		return (0);
// 	new_line = ft_lstlast(list);
// 	i = 0;
// 	while (new_line->content[i])
// 	{
// 			if (new_line->content[i] == '\n')
// 				return (1);
// 			i++;
// 	}
// 	return (0);
// }

// void	ft_read_file(int fd, t_list **list)
// {
// 	char	*buf;
// 	int		read_file;

// 	while (!ft_find_newline(*list) && read_file != 0)
// 	{
// 		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
// 		if (buf == NULL)
// 			return ;
// 		read_file = read(fd, buf, BUFFER_SIZE);
// 		if ((*list == NULL && read_file == 0) || read_file == -1)
// 		{
// 			free(buf);
// 			return ;
// 		}
// 		buf[read_file] = '\0';
// 		ft_lstadd_back(list, buf, read_file);
// 		free(buf);
// 	}
// }

// //!now ft_read_file

// void	ft_add_list(t_list *list, char **line)
// {
// 	int	i;
// 	int	len;

// 	len = 0;
// 	while (list)
// 	{
// 		i = 0;
// 		while (list->content[i])
// 		{
// 			if (list->content[i] == '\n')
// 			{
// 				len++;
// 				break ;
// 			}
// 			len++;
// 			i++;
// 		}
// 		list = list->next;
// 	}
// 	*line = malloc(sizeof(char) * (len + 1));
// }

// void	ft_create_list(t_list *list, char *line)
// {
// 	int		j;
// 	int		i;

// 	if (list == NULL)
// 		return ;
// 	ft_add_list(list, line);
// 	if (*line == NULL)
// 		return ;
// 	j = 0;
// 	while (list)
// 	{
// 		i = 0;
// 		while (list->content[i])
// 		{
// 			if (list->content[i] == '\n')
// 			{
// 				(*line)[j++] = list->content[i];
// 				break ;
// 			}
// 			(*line)[j++] = list->content[i++];
// 		}
// 		list = list->next;
// 	}
// 	(*line)[j] = '\0';
// }

// void	ft_switch_list(t_list **list)
// {
// 	t_list	*last;
// 	t_list	*clear_node;
// 	int		i;
// 	int		j;

// 	clear_node = malloc(sizeof(t_list));
// 	if (list == NULL || clear_node == NULL)
// 		return ;
// 	clear_node->next = NULL;
// 	last = ft_lstlast(*list);
// 	i = 0;
// 	while (last->content[i] && last->content[i] != '\n')
// 		i++;
// 	if (last->content[i] && last->content[i] != '\n')
// 		i++;
// 	clear_node->content = malloc(sizeof(char) * ((ft_strlen(last->content) - i) + 1));
// 	if (clear_node->content == NULL)
// 		return ;
// 	j = 0;
// 	while (last->content[i])
// 		clear_node->content[j++] = last->content[i++];
// 	clear_node->content[j] = '\0';
// 	ft_free_list(list);
// 	*list = clear_node;
// }

// int	ft_strlen(const char *str)
// {
// 	int	len;

// 	len = 0;
// 	while (*(str++))
// 		len++;
// 	return (len);
// }

// char	*get_next_line(int fd)
// {
// 	static t_list	*list = NULL;
// 	char			*line;
// 	int				read_file;

// 	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
// 		return (NULL);
// 	read_file = 1;
// 	line = NULL;

// 	printf("==============\n");
// 	// 1. ฟังชัน read ทำการอ่านไฟล์ที่ต้องการ
// 	ft_read_file(&list, &read_file);
// 	if (list == NULL)
// 		return (NULL);
// 	ft_create_list(list, &line); // สร้างพื้นที่เพื่อที่จะเก็บข้อมูล
// 	// printf("== res : %s ==\n", res);
// 	ft_switch_list(&list); /// สลับข้อมูลเพื่อที่จะสลับค่าและฟรีตัวเก่า
// 	// free(list);
// 	if (line[0] == '\0')
// 	{
// 		ft_free_list(list);
// 		list = NULL;
// 		free(line);
// 		return (NULL)
// 	}
// 	return (line);
// }

// int main()
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("59text.txt", O_RDONLY);
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (line == NULL)
// 			break;
// 		printf("%s", line);
// 		free(line);
// 	}
// }
