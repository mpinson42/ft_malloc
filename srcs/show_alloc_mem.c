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
	char *str;

	str = ft_itoa_base((int)g_env.tiny.tab[0], 16);
	ft_putstr("TINY : 0x");
	ft_putstr(str);
	free(str);
	ft_putchar('\n');
	i = -1;
	while (++i < PRE_ALLOC)
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
			ft_putstr(" octets\n");
		}
	}
}

static void	ft_small(int i, int getsize)
{
	char *str;

	str = ft_itoa_base((int)g_env.tiny.tab[0], 16);
	ft_putstr("SMALL : 0x");
	ft_putstr(str);
	free(str);
	ft_putchar('\n');
	i = -1;
	while (++i < PRE_ALLOC)
	{
		if (g_env.small.alloc[i] == 1)
		{
			ft_putstr("0x");
			str = ft_itoa_base((int)g_env.small.tab[i], 16);
			ft_putstr(str);
			free(str);
			ft_putstr(" - 0x");
			str = ft_itoa_base((int)g_env.small.tab[i + 1], 16);
			ft_putstr(str);
			free(str);
			ft_putstr(" : ");
			ft_putnbr((int)g_env.small.size[i]);
			ft_putstr(" octets\n");
		}
	}
}

static void	ft_large(int i, int getsize)
{
	char *s;

	s = ft_itoa_base((int)g_env.tiny.tab[0], 16);
	ft_putstr("LARGE : 0x");
	ft_putstr(s);
	free(s);
	ft_putchar('\n');
	i = -1;
	while (++i < PRE_ALLOC)
	{
		if (g_env.large.alloc[i] == 1)
		{
			ft_putstr("0x");
			s = ft_itoa_base((int)g_env.large.tab[i], 16);
			ft_putstr(s);
			free(s);
			ft_putstr(" - 0x");
			s = ft_itoa_base((int)g_env.large.tab[i] + g_env.large.size[i], 16);
			ft_putstr(s);
			free(s);
			ft_putstr(" : ");
			ft_putnbr((int)g_env.large.size[i]);
			ft_putstr(" octets\n");
		}
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
