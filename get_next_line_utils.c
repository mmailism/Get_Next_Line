/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammai <iammai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:13:01 by kpueankl          #+#    #+#             */
/*   Updated: 2024/01/08 17:51:53 by iammai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	temp = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!temp)
		return (NULL);
	while (s1[j])
		temp[i++] = s1[j++];
	j = 0;
	while (s2[j])
		temp[i++] = s2[j++];
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
char	*ft_strdup(const char *s1)
{
	char	*alt;
	char	n;
	int		i;

	if (!s1)
		return (NULL);
	n = ft_strlen(s1) + 1;
	alt = (char *)malloc(sizeof(char) * n);
	if (!alt)
		return (NULL);
	i = 0;
	while (i < n)
	{
		alt[i] = s1[i];
		i++;
	}
	alt[i] = 0;
	return (alt);
}
