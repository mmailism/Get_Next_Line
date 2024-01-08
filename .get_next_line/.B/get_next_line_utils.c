/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammai <iammai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:13:01 by kpueankl          #+#    #+#             */
/*   Updated: 2024/01/08 18:32:03 by iammai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstlast(t_list *list)
{
	if (list == NULL)
		return (NULL);
	while (list && list->next)
		list = list->next;
	return (list);
}

void	ft_lstadd_back(t_list **list, char *buf) // !next fix
{
	int		i;
	t_list	*last;
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	new_node->next = NULL;
	new_node->content = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (new_node->content == NULL)
		return ;
	i = 0;
	while (buf[i])
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

void	ft_free_list(t_list *list)
{
	t_list	*curr;
	t_list	*next;

	curr = list;
	while (curr)
	{
		free(curr->content);
		next = curr->next;
		free(curr);
		curr = next;
	}
}

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (*(str++))
		len++;
	return (len);
}

int	ft_find_newline(t_list *list)
{
	int		i;
	t_list	*new_line;

	if (list == NULL)
		return (0);
	new_line = ft_lstlast(list);
	i = 0;
	while (new_line->content[i])
	{
			if (new_line->content[i] == '\n')
				return (1);
			i++;
	}
	return (0);
}
