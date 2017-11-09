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
	char *str = ft_itoa_base((int)g_env.tiny.tab[0], 16);
	ft_putstr("TINY : 0x");
	ft_putstr(str);
	free(str);
	ft_putchar('\n');
	i = 0;
	while (i < PRE_ALLOC)
	{
		if (g_env.tiny.alloc[i] == 1)
		{
			ft_putstr("0x");
			str = ft_itoa_base((int)g_env.tiny.tab[i], 16);
			ft_putstr(str);
			free(str);
			ft_putstr(" - 0x");
			str = ft_itoa_base((int)g_env.tiny.tab[i + 1], 16);
			ft_putstr(str);
			free(str);
			ft_putstr(" : ");
			ft_putnbr((int)g_env.tiny.size[i]);
			ft_putstr(" octets");
			//ft_putnbr(g_env.tiny.size[i]);
			ft_putchar('\n');
		}
		i++;
	}
}

static void	ft_small(int i, int getsize)
{
	ft_putstr("SMALL : 0x");
	ft_putstr(ft_itoa_base((int)g_env.small.tab[0], 16));
	ft_putchar('\n');
	i = 0;
	while (i < PRE_ALLOC)
	{
		if (g_env.small.alloc[i] == 1  /*&& g_env.small.size[i] >= 10*/)
		{
			ft_putstr("0x");
			ft_putstr(ft_itoa_base((int)g_env.small.tab[i], 16));
			ft_putstr(" - 0x");
			ft_putstr(ft_itoa_base((int)g_env.small.tab[i + 1], 16));
			ft_putstr(" : ");
			ft_putnbr((int)g_env.small.size[i]);
			ft_putstr(" octets");
			//ft_putnbr(g_env.tiny.size[i]);
			ft_putchar('\n');
		}
		i++;
	}
}

static void	ft_large(int i, int getsize)
{
	ft_putstr("LARGE : 0x");
	ft_putstr(ft_itoa_base((int)g_env.large.tab[0], 16));
	ft_putchar('\n');
	i = 0;
	while (i < PRE_ALLOC)
	{
		if (g_env.large.alloc[i] == 1  /*&& g_env.large.size[i] >= 10*/)
		{
			ft_putstr("0x");
			ft_putstr(ft_itoa_base((int)g_env.large.tab[i], 16));
			ft_putstr(" - 0x");
			ft_putstr(ft_itoa_base((int)g_env.large.tab[i] + g_env.large.size[i], 16));
			ft_putstr(" : ");
			ft_putnbr((int)g_env.large.size[i]);
			ft_putstr(" octets");
			//ft_putnbr(g_env.tiny.size[i]);
			ft_putchar('\n');
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
