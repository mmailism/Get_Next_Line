/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammai <iammai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:13:01 by kpueankl          #+#    #+#             */
/*   Updated: 2023/12/14 16:46:39 by iammai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// # include <stdlib.h>
// # include <fcntl.h>
// # include <unistd.h>
// # include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 22
# endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <limits.h>

typedef struct s_list
{
	char			*data;
	int				fd_id;
	struct s_list	*next;
}					t_list;

// typedef struct s_list
// {
// 	char			*content;
// 	char			*backup;
// 	int				len;
// 	struct s_list	*next;
// }					t_list;

char	*get_next_line(int fd);

//A
void	ft_bzero(void *s, size_t n);
void	ft_read_list(t_list **list, int fd);
int	ft_new_line(t_list *list);
void	ft_create_list(t_list *list, char **line);
void	ft_re_list(t_list **list);
t_list	*ft_lstnew(char *content);
void	ft_lstadd_back(t_list **list, t_list *new);
t_list	*ft_lstlast(t_list *list);
void	ft_lstclear(t_list **list, void (*del)(void *));
void	*ft_calloc(size_t count, size_t n);

//C
size_t	find_line_ending(char *str, size_t i);
char	*get_string(char *str);
char	*read_the_line(char *str);
char	*free_and_null(char *buff1, char *buff2);
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char *buffer, char *content);


//D
void	ft_read_list(t_list **list, int fd);
int	ft_new_line(t_list *list);
void	ft_create_list(t_list *list, char **line);
void	ft_re_list(t_list **list);
t_list	*ft_lstnew(char *content);
void	ft_lstadd_back(t_list **list, t_list *new);
t_list	*ft_lstlast(t_list *list);
void	ft_lstclear(t_list **list, void (*del)(void *));
void	*ft_calloc(size_t count, size_t n);

//mix
t_list	*ft_clearnode_eof(t_list *lst);
t_list	*ft_update_backup(t_list *c_lst, char *new_line);
size_t	ft_strlen_nl(char *s, size_t mode);
char	*ft_checkread_malloc_t(char *old_str, char *buf, int mode);
t_list	*ft_newnode(int fd, t_list **lst);
char	*get_next_line(int fd);

#endif