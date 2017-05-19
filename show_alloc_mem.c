/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 15:38:20 by mpinson           #+#    #+#             */
/*   Updated: 2017/05/19 15:38:24 by mpinson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void ft_tiny(int i, int getsize)
{
	ft_putstr("TINY : 0x");
	ft_putstr(ft_itoa_base((int)env.tiny_start, 16));
	ft_putchar('\n');
	while(i < 100)
	{
		if(env.tiny[i] == 1)
		{
			ft_putstr("0x");
			ft_putstr(ft_itoa_base((int)env.tiny_start + (i * (getsize * TINY_SIZE)), 16));
			ft_putstr(" - 0x");
			ft_putstr(ft_itoa_base((int)env.tiny_start + ((i + 1) * (getsize * TINY_SIZE)), 16));
			ft_putstr(" : ");
			ft_putstr(ft_itoa_base((int)(getsize * TINY_SIZE), 16));
			ft_putstr(" octets | efficiant : ");
			ft_putnbr(env.tiny_alloc[i]);
			ft_putchar('\n');
		}
		i++;
	}
}

void ft_small(int i, int getsize)
{
	ft_putstr("SMALL : 0x");
	ft_putstr(ft_itoa_base((int)env.small_start, 16));
	ft_putchar('\n');
	while(i < 100)
	{
		if(env.small[i] == 1)
		{
			ft_putstr("0x");
			ft_putstr(ft_itoa_base((int)env.small_start + (i * (getsize * SMALL_SIZE)), 16));
			ft_putstr(" - 0x");
			ft_putstr(ft_itoa_base((int)env.small_start + ((i + 1) * (getsize * SMALL_SIZE)), 16));
			ft_putstr(" : ");
			ft_putstr(ft_itoa_base((int)(getsize * SMALL_SIZE), 16));
			ft_putstr(" octets | efficiant : ");
			ft_putnbr(env.small_alloc[i]);
			ft_putchar('\n');
		}
		i++;
	}
}

void ft_large(int i, int getsize)
{
	ft_putstr("LARGE : 0x");
	ft_putstr(ft_itoa_base((int)env.large_plage[0], 16));
	ft_putchar('\n');
	while(i < 100)
	{
		if(env.libre[i] == 1)
		{
			ft_putstr("0x");
			ft_putstr(ft_itoa_base((int)env.large_plage[i], 16));
			ft_putstr(" - 0x");
			ft_putstr(ft_itoa_base((int)env.large_plage[i] + env.size[i], 16));
			ft_putstr(" : ");
			ft_putnbr((int)env.size[i]);
			ft_putstr(" octets\n");
		}
		i++;
	}

}

void show_alloc_mem()
{
	int getsize;

	getsize = getpagesize();
	ft_tiny(0, getsize);
	ft_small(0, getsize);
	ft_large(0, getsize);
}
