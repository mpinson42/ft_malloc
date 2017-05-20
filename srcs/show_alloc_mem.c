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

static void	ft_tiny(int i, int getsize)
{
	ft_putstr("TINY : 0x");
	ft_putstr(ft_itoa_base((int)g_env.tiny_start, 16));
	ft_putchar('\n');
	while (i < 100)
	{
		if (g_env.tiny[i] == 1)
		{
			ft_putstr("0x");
			ft_putstr(ft_itoa_base((int)g_env.tiny_start +
				(i * (getsize * TINY_SIZE)), 16));
			ft_putstr(" - 0x");
			ft_putstr(ft_itoa_base((int)g_env.tiny_start + ((i + 1) *
				(getsize * TINY_SIZE)), 16));
			ft_putstr(" : ");
			ft_putstr(ft_itoa_base((int)(getsize * TINY_SIZE), 16));
			ft_putstr(" octets | efficiant : ");
			ft_putnbr(g_env.tiny_alloc[i]);
			ft_putchar('\n');
		}
		i++;
	}
}

static void	ft_small(int i, int getsize)
{
	ft_putstr("SMALL : 0x");
	ft_putstr(ft_itoa_base((int)g_env.small_start, 16));
	ft_putchar('\n');
	while (i < 100)
	{
		if (g_env.small[i] == 1)
		{
			ft_putstr("0x");
			ft_putstr(ft_itoa_base((int)g_env.small_start +
				(i * (getsize * SMALL_SIZE)), 16));
			ft_putstr(" - 0x");
			ft_putstr(ft_itoa_base((int)g_env.small_start + ((i + 1) *
				(getsize * SMALL_SIZE)), 16));
			ft_putstr(" : ");
			ft_putstr(ft_itoa_base((int)(getsize * SMALL_SIZE), 16));
			ft_putstr(" octets | efficiant : ");
			ft_putnbr(g_env.small_alloc[i]);
			ft_putchar('\n');
		}
		i++;
	}
}

static void	ft_large(int i, int getsize)
{
	ft_putstr("LARGE : 0x");
	ft_putstr(ft_itoa_base((int)g_env.large_plage[0], 16));
	ft_putchar('\n');
	while (i < 100)
	{
		if (g_env.libre[i] == 1)
		{
			ft_putstr("0x");
			ft_putstr(ft_itoa_base((int)g_env.large_plage[i], 16));
			ft_putstr(" - 0x");
			ft_putstr(ft_itoa_base((int)g_env.large_plage[i] +
				g_env.size[i], 16));
			ft_putstr(" : ");
			ft_putnbr((int)g_env.size[i]);
			ft_putstr(" octets\n");
		}
		i++;
	}
}

void		show_alloc_mem(void)
{
	int getsize;

	getsize = getpagesize();
	ft_tiny(0, getsize);
	ft_small(0, getsize);
	ft_large(0, getsize);
}
