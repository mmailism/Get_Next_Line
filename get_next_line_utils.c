/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mai <Mai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:13:01 by kpueankl          #+#    #+#             */
/*   Updated: 2024/01/15 21:53:09 by Mai              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	temp = count_list(s1, s2);
	if (!temp)
		return (free(s1), NULL);
	while (s1[j])
		temp[i++] = s1[j++];
	j = 0;
	while (s2[j])
		temp[i++] = s2[j++];
	temp[i] = '\0';
	return (temp);
}

char	*count_list(char *list, char *buffer)
{
	size_t	i;
	size_t	cnt_list;
	size_t	cnt_buffer;
	char	*tmp;
	i = 0;
	if (list)
	{
		if (buffer[0] == '\0')
			return (NULL);
		while (buffer[i] != '\0')
		{
			if (buffer[i] == '\n')
				return (NULL);
			i++;
		}
		return (buffer);
	}
	cnt_list = ft_strlen(list);
	cnt_buffer = ft_strlen(buffer);
	tmp = (char *)malloc(cnt_list + cnt_buffer + 1);
	if (!tmp)
		return (free(tmp), NULL);
	return (tmp);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	tmp = malloc(len + 1);
	if (!tmp)
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
			tmp[j++] = s[i];
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	s_len;
	size_t	i;

	i = 0;
	s_len = ft_strlen(s);
	dup = (char *)malloc((s_len * sizeof(char)) + 1);
	if (dup == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
