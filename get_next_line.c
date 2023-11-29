/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammai <iammai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:13:01 by kpueankl          #+#    #+#             */
/*   Updated: 2023/11/29 16:39:03 by iammai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_create_list(t_list *list, char **res)
{
	int		len;
	int		i;
	t_list	*tmp;

	tmp = list; //กำหนดให้ 1 ตัวแปร เท่ากับ ที่รับมา
	while (tmp) // เริ่มลูป
		tmp = tmp->next; //แล้วส่ง tmp เข้า linklist ตัวถัดไป
	*res = (char *)malloc(sizeof(**res));
	if (!res)
		return ;
	// printf("len2 : %d\n", len);
	len = 0;
	while (list && list->content)
	{
		i = 0;
		while (list->content[i])
			(*res)[len++] = list->content[i++];
		list = list->next;
	}
	printf("len : %d\n", len);
}

void	ft_switch_list(t_list **list)
{
	t_list	*tmp;
	t_list	*new_node;
	char	*content;
	int		i;
	int		k;

	k = 0;
	tmp = ft_lstlast(*list);
	if (!tmp)
		return ;
	content = tmp->content; // set content in linklist
	k = tmp->len; // set k in linklist
	tmp->content = NULL;
	// printf("content : %s\n", content);
	ft_lstclear(list, free); //clear free linklist
	if (content[k] != '\0')
	{
		i = 0;
		while (content[k] != '\0')
			content[i++] = content[k++];
		new_node = ft_lstnew(content);
		ft_lstadd_back(list, new_node);
	}
	else
		free(content);
}

int	ft_find_newline(t_list *list)
{
	int	i;
	
	if (!list)
		return (0);
	i = 0;
	while (list->content[i] != '\0')
	{
		if (list->content[i] == '\n')
		{
			list->len = ++i;
			return(i);
		}
		i++;
	}
	list->len = i;
	return (i);
}

void	ft_read_file(t_list **list, int fd)
{
	t_list	*node_s;
	char	*buf;
	int		read_file;

	// printf("\n== fd : %d ==", fd);
	buf = malloc(sizeof(char) * BUFFER_SIZE + 1); //กำหนดให้ ตัวแปรมีค่าเท่ากับ BUFFER_SIZE + 1
	ft_bzero(buf, BUFFER_SIZE); // set 0 ให้กับ buf
	while (!ft_find_newline(*list) && read_file != 0) // เข้าลูป ถ้าไม่เจอ \n
	{
		// printf("\n{read_file : %d}\nbuf : %s\n", read_file, buf);
		node_s = ft_lstnew(buf); // กำหนดให้ linklist
		printf("\nTEST\n");
		read_file = read(fd ,buf, BUFFER_SIZE); // ทำการ read
		if ((*list == NULL && read_file == 0) || read_file == -1)
		{
			free(buf);
			return ;
		}
		// printf("\nTEST\n");
		node_s->content[BUFFER_SIZE] = '\0';
		ft_lstadd_back(list, node_s); //เพิ่มเข้าไปใน linklist
		// printf("\n{read_file : %d}\nbuf : %s\n", read_file, buf);
	}
	printf("buffer_size : %d\n", BUFFER_SIZE);
}

char	*get_next_line(int fd) // main funtion เป็น char
{ // กำหนดตัวแปร ตัวที่ 1 ค่าที่จะส่งไปฟังชันอื่นๆ ตัวที่ 2 ตัวแปรที่จะ output
	static t_list	*list = NULL;
	char			*res;

	res = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	printf("==============\n");
	ft_read_file(&list, fd); // ฟังชัน read ทำการอ่านไฟล์ที่ต้องการ
	// printf("\nTEST\n");
	if (!list)
	{
		free(list);
		return (NULL);
	}
	ft_create_list(list, &res); // สร้างพื้นที่เพื่อที่จะเก็บข้อมูล
	// printf("== res : %s ==\n", res);
	ft_switch_list(&list); /// สลับข้อมูลเพื่อที่จะสลับค่าและฟรีตัวเก่า
	// free(list);
	return (res);
}

int main()
{
	int fd;
	
	fd = open("43_no_nl.txt", O_RDONLY);

	printf("-- out 1 : %s --\n", get_next_line(fd));
	printf("-- out 2 : %s --\n", get_next_line(fd));
	printf("-- out 3 : %s --\n", get_next_line(fd));
	printf("-- out 4 : %s --\n", get_next_line(fd));
	printf("==============\n");
	close (fd);
	return(0);
}
