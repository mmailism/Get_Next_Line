/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpueankl <kpueankl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:13:01 by kpueankl          #+#    #+#             */
/*   Updated: 2024/01/05 16:55:57 by kpueankl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
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

int	found_new_line(t_list *stash)
{
	int		i;

	if (stash == NULL)
		return (0);
	i = 0;
	if (stash == NULL)
		return (0);
	while (stash->next != NULL)
		stash = stash->next;
	while (stash->content[i])
	{
		if (stash->content[i] == '\n')
			return (1);
	i++;
	}
	return (0);
}

void	generate_line(char **line, t_list *stash)
{
	int	i;
	int	len;

	len = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		stash = stash->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
}

void	free_stash(t_list *stash)
{
	t_list	*current;
	t_list	*next;

	current = stash;
	while (current)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
}
