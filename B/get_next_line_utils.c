#include "get_next_line.h"

char	*check_list(char *list, char *buff)
{
	char	*tmp;
	size_t	i;
	size_t	cnt_list_buff;
	// size_t	cnt_buff;

	i = 0;
	if (list)
		return (NULL);
	if (list)
	{
		if (buff[0] == '\0')
			return (NULL);
		while (buff[i] != '\0')
		{
			if (buff[i] == '\n')
				return (NULL);
			i++;
		}
		return (buff);
	}
	cnt_list_buff = ft_strlen(list, 1) + ft_strlen(buff, 1);
	// cnt_buff = ft_strlen(buff, 1);
	tmp = (char *)malloc(cnt_list_buff + 1);
	if (!tmp)
		return (free(tmp), NULL);
	return (tmp);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	temp = (char *)malloc((ft_strlen(s1, 2) + ft_strlen(s2, 1) + 1));
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

size_t	ft_strlen(const char *str, size_t mem)
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

char	*get_lst(t_list *list)
{
	char	*lst_n;
	int		i;
	int		lstlen;

	if (!list)
		return (NULL);
	i = 0;
	lstlen = ft_strlen(list->content, 2);
	if (lstlen == 0)
		return (NULL);
	lst_n = (char *)malloc(lstlen + 1);
	if (!lst_n)
		return (NULL);
	while (list->content[i] != '\0' && list->content[i] != '\n')
	{
		lst_n[i] = list->content[i];
		i++;
	}
	if (list->content[i] == '\n')
		lst_n[i++] = '\n';
	lst_n[i] = '\0';
	list = swap_lst(list, lst_n);
	if (!list)
		return (NULL);
	return (lst_n);
}

t_list	*swap_lst(t_list *list, char *lst_n)
{
	char	*tmp;
	char	*current;
	size_t	i;
	size_t	cnt_m;

	current = list->content;
	current = current + ft_strlen(current, 2);
	cnt_m = ft_strlen(current, 1);
	tmp = (char *)malloc(cnt_m + 1);
	if (!tmp)
	{
		free(lst_n);
		return (NULL);
	}
	i = 0;
	while (current[i] != '\0')
	{
		tmp[i] = current[i];
		i++;
	}
	tmp[i] = '\0';
	free(list->content);
	list->content = tmp;
	return (list);
}
