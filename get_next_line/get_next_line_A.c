/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_A.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpueankl <kpueankl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:13:01 by kpueankl          #+#    #+#             */
/*   Updated: 2023/11/20 15:25:10 by kpueankl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	
}

int main()
{
	int fd;
	
	fd = open("59text.txt", O_RDONLY);

	printf("test1 :%s\n", get_next_line(fd));
	printf("test2 :%s\n", get_next_line(fd));
	printf("test3 :%s\n", get_next_line(fd));
	printf("test4 :%s\n", get_next_line(fd));
	close (fd);
	return(0);
}