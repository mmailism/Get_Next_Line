#include "get_next_line.h"

int	ft_len_newline(t_list *list)
{
	int	i;
	int	len;

	if (list == NULL)
		return (NULL);
	len = 0;
	//list != NULL
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
			len++;
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
		return (NULL);
	k = 0;
	while (list)
	{
		i = 0;
		while (list->str_buf[i])
		{
			if (list->str_buf[i] == '\n')
			{
				str[k++] = '\n';
				str[k] = '\0';
				return ;
			}
			str[k++] = list->str_buf[i++];
		}
		list = list->next;
	}
	str[k] = '\0';
}
