/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammai <iammai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:55:44 by kpueankl          #+#    #+#             */
/*   Updated: 2023/11/21 16:52:42 by iammai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_found_newline(t_list *list)
{
	int	i;

	if (list == NULL)
		return ;
	while (list)
	{
		i = 0;
		while (list->str_buf[i] && i < BUFFER_SIZE)
		{
			if (list->str_buf[i] == '\n')
				return (i);
			i++;
		}
		list = list->next;
	}
	return (0);
}

t_list	*ft_find_lastnode(t_list *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

int	ft_len_newline(t_list *list)
{
	int	i;
	int	len;

	if (list == NULL)
		return (NULL);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->str_buf[i])
		{
			if (list->str_buf[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			++len;
		}
		list = list->next;
	}
	return (len);
}

void	ft_copy_str(t_list *list, char *str)
{
	int	i;
	int	k;

	if (list == NULL)
		return ;
	k = 0;
	while (list)
	{
		i = 0;
		while (list->str_buf[i])
		{
			if (list->str_buf[i] == '\n')
			{
				str[++k] = '\n';
				str[k] = '\0';
				return ;
			}
			str[k++] = list->str_buf[++i]; //cut the line is ++i
		}
		list = list->next;
	}
	str[k] = '\0';
}

void	dealloc(t_list **list, t_list *clean_node, char *buf)
{
	t_list	*tmp;

	if (*list == NULL)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (clean_node->str_buf[0])
		*list = clean_node;
	else
	{
		free(buf);
		free(clean_node);
	}
}
