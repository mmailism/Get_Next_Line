/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammai <iammai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:13:01 by kpueankl          #+#    #+#             */
/*   Updated: 2023/12/22 19:32:17 by iammai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_stash(t_list *line)
{
	t_list	*current;
	t_list	*next;

	current = line;
	while (current)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
}

char	*trim_last_list_element_helper(t_list *last, int i)
{
	int		j;
	int		len;
	char	*trimmed_content;

	len = 0;
	while (last->content[len])
		len++;
	trimmed_content = malloc(sizeof(char) * (len - i + 1));
	if (trimmed_content == NULL)
		return (NULL);
	j = 0;
	while (last->content[i])
		trimmed_content[j++] = last->content[i++];
	trimmed_content[j] = '\0';
	return (trimmed_content);
}

t_list	*ft_lstlast(t_list *list)
{
	if (!list )
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

void	add_join_next(t_list *line, char *buf, int read_list)
{
	t_list	*new_node;
	t_list	*last;
	int		i;

	new_node = malloc(sizeof(t_list));
	new_node->content = malloc(sizeof(char) * (read_list + 1));
	if (!new_node->content)
		return ;
	new_node->next = NULL;
	i = 0;
	while (buf[i] && i < read_list)
	{
		new_node->content[i] = buf[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (!line)
		line = new_node;
	else
	{
		last = ft_lstlast(line);
		last->next = new_node;
	}
}

void	generate_line(t_list *line, char *res)
{
	int	i;
	int	len;
	
	len = 0;
	while (line)
	{
		i = 0;
		while (line->content[i])
		{
			if (line->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		line = line->next;
	}
	res = malloc(sizeof(char) * (len + 1));
}
