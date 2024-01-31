/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammai <iammai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:13:01 by kpueankl          #+#    #+#             */
/*   Updated: 2024/01/31 14:15:43 by iammai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* function ft_strlen mem 1 count string || mem 2 count string and "\n" */

size_t	ft_strlen(char *str, size_t mem)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	if (mem == 1)
	{
		while (str[i] != '\0')
			i++;
	}
	else if (mem == 2)
	{
		if (str[0] == '\0')
			return (0);
		while (str[i] != '\0' && str[i] != '\n')
			i++;
		if (str[i] == '\n')
			i++;
	}
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	if (c == '\0')
	{
		while (*s != '\0')
			s++;
		return ((char *)s);
	}
	while (*s != (char)c)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}

char	*ft_strjoin(char *tmp, char *buff)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	if (!tmp || !buff)
		return (NULL);
	temp = (char *)malloc((ft_strlen(tmp, 1) + ft_strlen(buff, 1) + 1));
	if (!temp)
		return (free(tmp), NULL);
	while (tmp[j])
		temp[i++] = tmp[j++];
	j = 0;
	while (buff[j])
		temp[i++] = buff[j++];
	temp[i] = '\0';
	return (temp);
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

char	*ft_strdup(char *s)
{
	char	*dup;
	size_t	s_len;
	size_t	i;

	i = 0;
	s_len = ft_strlen(s, 1);
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
