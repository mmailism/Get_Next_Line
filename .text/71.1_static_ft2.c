/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   71_static_ft2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdanchal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:50:59 by kdanchal          #+#    #+#             */
/*   Updated: 2023/11/13 15:41:26 by kdanchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	ft_1(void)
{
//	static int x;
	int x ;

	x = x + 1;
	printf("ft_1 x=%d\n", x);
}

void	ft_2(void)
{
//	static int y;
	int	y;

	y = y+1;
	printf("ft_2 	y=%d\n",y);
}
	
static void	ft_3 (void)
{
	printf("\nft_3");
}

void	ft_4(void)
{
	printf("\nft_4");
	ft_3();
}

void	ft_5(void)
{
	printf("\nft_5");
}

/*
int	main (void)
{
	ft_1();
	ft_1();
	ft_1();
	ft_2();
	ft_2();
	ft_1();
	ft_2();

	ft_3();
	ft_4();
	ft_5();
}
*/
