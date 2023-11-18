#include "get_next_line.h"

t_list	*ft_lstnew(char *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->length = 0;
	new_node->next = NULL;
	return (new_node);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = ft_lstlast(*lst);
	temp->next = new;
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp_lst;

	if (!lst || !del)
		return ;
	while (*lst != NULL)
	{
		temp_lst = *lst;
		*lst = (*lst)->next;
		free(temp_lst->content);
		free(temp_lst);
	}
	*lst = NULL;
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*arr;
	size_t			alloc_size;
	size_t			i;
	unsigned char	*cast_s;

	alloc_size = nmemb * size;
	if (!alloc_size || alloc_size / nmemb != size)
		return (NULL);
	arr = malloc(alloc_size);
	if (arr == NULL)
		return (NULL);
	i = 0;
	cast_s = arr;
	while (i < alloc_size)
	{
		cast_s[i] = '\0';
		i++;
	}
	return (cast_s);
}

static int	is_new_line(t_list *cache)
{
	int		i;

	cache = ft_lstlast(cache);
	if (!cache)
		return (0);
	i = 0;
	while (cache->content[i] != '\0')
	{
		if (cache->content[i] == '\n')
		{
			cache->length = ++i;
			return (1);
		}
		i++;
	}
	cache->length = i;
	return (0);
}

static void	read_line(t_list **cache, int fd)
{
	int		output;
	char	*buffer;
	t_list	*new_node;

	output = 0;
	while (!is_new_line(*cache))
	{
		buffer = NULL;
		new_node = ft_lstnew(buffer);
		new_node->content = ft_calloc(sizeof(*buffer), (BUFFER_SIZE + 1));
		output = read(fd, new_node->content, BUFFER_SIZE);
		if (output == 0 || output == -1)
		{
			free(new_node->content);
			free(new_node);
			return ;
		}
		new_node->content[BUFFER_SIZE] = '\0';
		ft_lstadd_back(cache, new_node);
	}
}

static void	create_line(t_list *cache, char **line)
{
	int		ln_size;
	int		i;
	t_list	*temp;

	temp = cache;
	ln_size = 0;
	while (temp)
	{
		ln_size = ln_size + temp->length;
		temp = temp->next;
	}
	if (!ln_size)
		return ;
	*line = malloc(sizeof(**line) * (ln_size + 1));
	if (!line)
		return ;
	ln_size = 0;
	while (cache && cache->content)
	{
		i = 0;
		while (cache->content[i] && i < cache->length)
			(*line)[ln_size++] = cache->content[i++];
		cache = cache->next;
	}
	(*line)[ln_size] = '\0';
}

static void	refactor_line(t_list **cache)
{
	t_list	*temp;
	t_list	*new_node;
	char	*content;
	int		i;
	int		size;

	size = 0;
	temp = ft_lstlast(*cache);
	if (!temp)
		return ;
	content = temp->content;
	size = temp->length;
	temp->content = NULL;
	ft_lstclear(cache, free);
	i = 0;
	if (content[size] != '\0')
	{
		while (content[size] != '\0')
			content[i++] = content[size++];
		content[i] = '\0';
		new_node = ft_lstnew(content);
		ft_lstadd_back(cache, new_node);
	}
	else
		free(content);
}

char	*get_next_line(int fd)
{
	static t_list	*cache = NULL;
	char			*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_line(&cache, fd);
	if (!cache)
		return (NULL);
	create_line(cache, &line);
	refactor_line(&cache);
	return (line);
}

int	main(void)
{
	int	fd = open("59text.txt", O_RDONLY);

	printf("==main==%s", get_next_line(fd));
	printf("==main==%s", get_next_line(fd));
	printf("==main==%s", get_next_line(fd));
	close (fd);
	return(0);
}