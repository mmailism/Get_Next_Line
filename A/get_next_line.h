#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <limits.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

char	*get_next_line(int fd);
char	*read_line(int fd, char *buffer, char *list);
char	*ft_strjoin(char *list, char *buffer);
char	*count_list(char *list, char *buffer);
size_t	ft_strlen(char const *str);
static void	set_zero(char *ptr, int size);
void	*get_list(char *list);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s);

#endif