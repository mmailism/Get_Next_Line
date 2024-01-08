/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_F.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpueankl <kpueankl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:07:36 by rrouille          #+#    #+#             */
/*   Updated: 2024/01/05 16:54:52 by kpueankl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	prepare_stash_from_file(int fd, t_list **stash)
{
	char	*buffer;
	int		num_bytes;

	num_bytes = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (!found_new_line(*stash) && num_bytes != 0)
	{
		if (buffer == NULL)
			return ;
		num_bytes = read(fd, buffer, BUFFER_SIZE);
		if ((*stash == NULL && num_bytes == 0) || num_bytes == -1)
		{
			free(buffer);
			if (num_bytes == -1)
				free_stash(*stash);
			*stash = NULL;
			return ;
		}
		buffer[num_bytes] = '\0';
		append_buffer_to_stash(stash, buffer, num_bytes);
	}
	free(buffer);
}

void	append_buffer_to_stash(t_list **stash, char *buffer, int num_bytes)
{
	int		i;
	t_list	*last;
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	new_node->content = malloc(sizeof(char) * (num_bytes + 1));
	if (new_node == NULL
		|| new_node->content == NULL)
		return ;
	new_node->next = NULL;
	i = 0;
	while (buffer[i] && i < num_bytes)
	{
		new_node->content[i] = buffer[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (*stash == NULL)
		*stash = new_node;
	else
	{
		last = ft_lstlast(*stash);
		last->next = new_node;
	}
}

void	read_line_from_stash(t_list *stash, char **line)
{
	int	i;
	int	j;

	if (stash == NULL)
		return ;
	generate_line(line, stash);
	if (*line == NULL)
		return ;
	j = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				(*line)[j++] = stash->content[i];
				break ;
			}
			(*line)[j++] = stash->content[i++];
		}
		stash = stash->next;
	}
	(*line)[j] = '\0';
}

t_list	*trim_last_list_element(t_list **lst)
{
	t_list	*last;
	t_list	*clean_node;
	int		i;

	clean_node = malloc(sizeof(t_list));
	if (lst == NULL || clean_node == NULL)
	{
		*lst = clean_node;
		return (NULL);
	}
	clean_node->next = NULL;
	last = ft_lstlast(*lst);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content[i] == '\n')
		i++;
	clean_node->content = trim_last_list_element_helper(last, i);
	if (clean_node->content == NULL)
		return (NULL);
	free_stash(*lst);
	*lst = clean_node;
	return (clean_node);
}

char	*get_next_line(int fd)
{
	static t_list	*stash = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	prepare_stash_from_file(fd, &stash);
	if (stash == NULL)
		return (NULL);
	read_line_from_stash(stash, &line);
	trim_last_list_element(&stash);
	if (line[0] == '\0')
	{
		free_stash(stash);
		stash = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

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