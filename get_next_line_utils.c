/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammai <iammai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:13:01 by kpueankl          #+#    #+#             */
/*   Updated: 2023/11/24 16:10:44 by iammai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list  *ft_lstnew(char *content)
{
    t_list  *new_node;

    new_node = malloc(sizeof(*new_node));
    if (!new_node)
        return (NULL);
    new_node->content = content;
    new_node->next = NULL;
    return (new_node);
}

void    ft_lstadd_back(t_list **list, t_list *new)
{
    t_list  *temp;

    if (!list || !new)
        return ;
    if (!(*list))
    {
        *list = new;
        return ;
    }
    temp = *list;
    while (temp->next)
        temp = temp->next;
    temp->next = new;
}

t_list  *ft_lstlast(t_list *list)
{
    if (list == NULL)
        return (NULL);
    while (list->next)
        list = list->next;
    return (list);
}

void    ft_lstclear(t_list **list, void (*del)(void *))
{
    if (!list || !del || !(*list))
        return ;
    ft_lstclear(&(*list)->next, del);
    del((*list)->content);
    free(*list);
    *list = NULL;
}

void    ft_bzero(void *s, size_t n)
{
    unsigned char   *i;
    size_t          j;

    i = s;
    j = 0;
    if (n == 0)
        return ;
    while (j < n)
    {
        i[j] = 0;
        j++;
    }
}
