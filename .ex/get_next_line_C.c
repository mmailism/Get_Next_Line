// #include "get_next_line.h"

// static void	read_line(t_line **cache, int fd);
// static int	is_new_line(t_line *cache);
// static void	create_line(t_line *cache, char **line);
// static void	refactor_line(t_line **cache);

// char	*get_next_line(int fd)
// {
// 	static t_line	*cache = NULL;
// 	char			*line;

// 	line = NULL;
// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	read_line(&cache, fd);
// 	if (!cache)
// 		return (NULL);
// 	create_line(cache, &line);
// 	refactor_line(&cache);
// 	return (line);
// }

// static void	read_line(t_line **cache, int fd)
// {
// 	int		output;
// 	char	*buffer;
// 	t_line	*new_node;

// 	output = 0;
// 	while (!is_new_line(*cache))
// 	{
// 		buffer = NULL;
// 		new_node = ft_lstnew(buffer);
// 		new_node->content = ft_calloc(sizeof(*buffer), (BUFFER_SIZE + 1));
// 		output = read(fd, new_node->content, BUFFER_SIZE);
// 		if (output == 0 || output == -1)
// 		{
// 			free(new_node->content);
// 			free(new_node);
// 			return ;
// 		}
// 		new_node->content[BUFFER_SIZE] = '\0';
// 		ft_lstadd_back(cache, new_node);
// 	}
// }

// static int	is_new_line(t_line *cache)
// {
// 	int		i;

// 	cache = ft_lstlast(cache);
// 	if (!cache)
// 		return (0);
// 	i = 0;
// 	while (cache->content[i] != '\0')
// 	{
// 		if (cache->content[i] == '\n')
// 		{
// 			cache->length = ++i;
// 			return (1);
// 		}
// 		i++;
// 	}
// 	cache->length = i;
// 	return (0);
// }

// static void	create_line(t_line *cache, char **line)
// {
// 	int		ln_size;
// 	int		i;
// 	t_line	*temp;

// 	temp = cache;
// 	ln_size = 0;
// 	while (temp)
// 	{
// 		ln_size = ln_size + temp->length;
// 		temp = temp->next;
// 	}
// 	if (!ln_size)
// 		return ;
// 	*line = malloc(sizeof(**line) * (ln_size + 1));
// 	if (!line)
// 		return ;
// 	ln_size = 0;
// 	while (cache && cache->content)
// 	{
// 		i = 0;
// 		while (cache->content[i] && i < cache->length)
// 			(*line)[ln_size++] = cache->content[i++];
// 		cache = cache->next;
// 	}
// 	(*line)[ln_size] = '\0';
// }

// static void	refactor_line(t_line **cache)
// {
// 	t_line	*temp;
// 	t_line	*new_node;
// 	char	*content;
// 	int		i;
// 	int		size;

// 	size = 0;
// 	temp = ft_lstlast(*cache);
// 	if (!temp)
// 		return ;
// 	content = temp->content;
// 	size = temp->length;
// 	temp->content = NULL;
// 	ft_lstclear(cache, free);
// 	i = 0;
// 	if (content[size] != '\0')
// 	{
// 		while (content[size] != '\0')
// 			content[i++] = content[size++];
// 		content[i] = '\0';
// 		new_node = ft_lstnew(content);
// 		ft_lstadd_back(cache, new_node);
// 	}
// 	else
// 		free(content);
// }

// t_line	*ft_lstnew(char *content)
// {
// 	t_line	*new_node;

// 	new_node = malloc(sizeof(*new_node));
// 	if (!new_node)
// 		return (NULL);
// 	new_node->content = content;
// 	new_node->length = 0;
// 	new_node->next = NULL;
// 	return (new_node);
// }

// t_line	*ft_lstlast(t_line *lst)
// {
// 	if (!lst)
// 		return (NULL);
// 	while (lst->next != NULL)
// 	{
// 		lst = lst->next;
// 	}
// 	return (lst);
// }

// void	ft_lstadd_back(t_line **lst, t_line *new)
// {
// 	t_line	*temp;

// 	if (!new)
// 		return ;
// 	if (!*lst)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	temp = ft_lstlast(*lst);
// 	temp->next = new;
// }

// void	ft_lstclear(t_line **lst, void (*del)(void *))
// {
// 	t_line	*temp_lst;

// 	if (!lst || !del)
// 		return ;
// 	while (*lst != NULL)
// 	{
// 		temp_lst = *lst;
// 		*lst = (*lst)->next;
// 		free(temp_lst->content);
// 		free(temp_lst);
// 	}
// 	*lst = NULL;
// }

// void	*ft_calloc(size_t nmemb, size_t size)
// {
// 	void			*arr;
// 	size_t			alloc_size;
// 	size_t			i;
// 	unsigned char	*cast_s;

// 	alloc_size = nmemb * size;
// 	if (!alloc_size || alloc_size / nmemb != size)
// 		return (NULL);
// 	arr = malloc(alloc_size);
// 	if (arr == NULL)
// 		return (NULL);
// 	i = 0;
// 	cast_s = arr;
// 	while (i < alloc_size)
// 	{
// 		cast_s[i] = '\0';
// 		i++;
// 	}
// 	return (cast_s);
// }

// int main()
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("big_line_no_nl.txt", O_RDONLY);
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (line == NULL)
// 			break;
// 		printf("%s\n", line);
// 		free(line);
// 	}
// }
