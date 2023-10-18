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
	return (len)
}

void	ft_copy_string(t_list *list, char *str)
{
	
}
