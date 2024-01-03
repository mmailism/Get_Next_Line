/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_A.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammai <iammai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:13:01 by kpueankl          #+#    #+#             */
/*   Updated: 2023/11/23 15:54:40 by iammai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstnew(char *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
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

t_list	*ft_lstlast(t_list *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	ft_lstclear(t_list **list, void (*del)(void *))
{
	if (!list || !del || !(*list))
		return ;
	ft_lstclear(&(*list)->next, del);
	del((*list)->content);
	free(*list);
	*list = NULL;
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*i;
	size_t			j;

	i = s;
	j = 0;
	if (n == 0)
		return ;
	while (j < n)
	{
		i[j] = 0;
		j++;
	}
}

void	ft_create_list(t_list *list, char **res)
{
	int		len;
	int		i;
	t_list	*tmp;

	tmp = list; //กำหนดให้ 1 ตัวแปร เท่ากับ ที่รับมา
	while (tmp) // เริ่มลูป
		tmp = tmp->next; //แล้วส่ง tmp เข้า linklist ตัวถัดไป
	*res = (char *)malloc(sizeof(BUFFER_SIZE + 1)); //
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
	printf("content : %s\n", content);
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

	list = ft_lstlast(list);
	if (!list)
		return (0);
	while (list->content[i] != '\0')
	{
		i = 0;
		if (list->content[i] == '\n')
		{
			list->len = ++i;
			return (1);
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

	printf("\n== fd : %d ==", fd);
	read_file = 0;
	buf = (char *)malloc(BUFFER_SIZE + 1); //กำหนดให้ ตัวแปรมีค่าเท่ากับ BUFFER_SIZE + 1
	ft_bzero(buf, BUFFER_SIZE); // set 0 ให้กับ buf
	while (!ft_find_newline(*list)) // เข้าลูป ถ้าไม่เจอ \n
	{
		// printf("\n{read_file : %d}\nbuf : %s\n", read_file, buf);
		node_s = ft_lstnew(buf); // กำหนดให้ linklist
		read_file = read(fd ,buf, BUFFER_SIZE); // ทำการ read
		if (read_file == 0 || read_file == -1)
		{
			free(buf);
			return ;
		}
		node_s->content[BUFFER_SIZE] = '\0';
		ft_lstadd_back(list, node_s); //เพิ่มเข้าไปใน linklist ข้างหลัง
		printf("\n{read_file : %d}\nbuf : %s\n", read_file, buf);
	}
}

char	*get_next_line(int fd) // main funtion เป็น char
{ // กำหนดตัวแปร ตัวที่ 1 ค่าที่จะส่งไปฟังชันอื่นๆ ตัวที่ 2 ตัวแปรที่จะ output
	static t_list	*list = NULL;
	char			*res;

	res = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	printf("==============");
	ft_read_file(&list, fd); // ฟังชัน read ทำการอ่านไฟล์ที่ต้องการ
	if (!list)
		return (NULL);
	ft_create_list(list, &res); // สร้างพื้นที่เพื่อที่จะเก็บข้อมูล
	// printf("== res : %s ==\n", res);
	ft_switch_list(&list); /// สลับข้อมูลเพื่อที่จะสลับค่าและฟรีตัวเก่า
	return (res);
}

int main()
{
	int fd;
	
	fd = open("59text.txt", O_RDONLY);

	printf("-- out 1 : %s --\n", get_next_line(fd));
	printf("-- out 2 : %s --\n", get_next_line(fd));
	printf("-- out 3 : %s --\n", get_next_line(fd));
	printf("-- out 4 : %s --\n", get_next_line(fd));
	printf("==============\n");
	close (fd);
	return(0);
}