/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 15:37:56 by mpinson           #+#    #+#             */
/*   Updated: 2017/05/20 15:06:57 by mpinson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	ft_p1_2(int size, int i)
{
	g_env.tiny.alloc_max[i] = 1;
	g_env.tiny.size_max[i] = size;
	g_env.tiny.nb_alloc++;
}

static void	*ft_p1(int size)
{
	int i;

	i = 0;
	while (g_env.tiny.alloc[i] != 0 && g_env.tiny.alloc[i] != -1)
		i++;
	if (g_env.tiny.alloc[i] == 0)
	{
		i = 0;
		while (g_env.tiny.alloc_max[i] != 0 && g_env.tiny.alloc_max[i] != -1)
			i++;
		if (g_env.tiny.alloc_max[i] == 0)
			return (NULL);
		if (g_env.tiny.nb_alloc % 4 == 0)
			g_env.tiny.tab_max[i] = mmap(g_env.tiny.plage + (int)(getpagesize()
				* 0.25 * (i + g_env.tiny.nb_alloc)), size,
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		else
			g_env.tiny.tab_max[i] = g_env.tiny.plage +
		(int)(getpagesize() * 0.25 * (i + g_env.tiny.nb_alloc));
		ft_p1_2(size, i);
		return (g_env.tiny.tab_max[i]);
	}
	g_env.tiny.alloc[i] = 1;
	g_env.tiny.size[i] = size;
	return (g_env.tiny.tab[i]);
}

static void	*ft_p2(int size)
{
	int i;

	i = 0;
	while (g_env.small.alloc[i] != 0 && g_env.small.alloc[i] != -1)
		i++;
	if (g_env.small.alloc[i] == 0)
	{
		i = 0;
		while (g_env.small.alloc_max[i] != 0 && g_env.small.alloc_max[i] != -1)
			i++;
		if (g_env.small.alloc_max[i] == 0)
			return (NULL);
		g_env.small.tab_max[i] = mmap(g_env.small.plage + (int)(getpagesize() *
			(i + g_env.small.nb_alloc)), size,
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		g_env.small.alloc_max[i] = 1;
		g_env.small.size_max[i] = size;
		g_env.small.nb_alloc++;
		return (g_env.small.tab_max[i]);
	}
	g_env.small.alloc[i] = 1;
	g_env.small.size[i] = size;
	return (g_env.small.tab[i]);
}

static void	*ft_p3(int size)
{
	int i;

	i = 0;
	while (g_env.large.alloc[i] != 0 && g_env.large.alloc[i] != -1)
		i++;
	if (g_env.large.alloc[i] == 0)
		return (NULL);
	g_env.large.tab[i] = mmap(NULL, size, PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_PRIVATE, -1, 0);
	g_env.large.alloc[i] = 1;
	g_env.large.size[i] = size;
	return (g_env.large.tab[i]);
}

void		*malloc(size_t size)
{
	void		*str;
	int			getsize;
	static int	i = 1;

	getsize = getpagesize();
	if (i == 1)
	{
		i = 0;
		ft_init(getsize);
	}
	if (size > 0 && size <= getsize * 0.25)
		return (ft_p1(size));
	else if (size > getsize * 0.25 && size < getsize)
		return (ft_p2(size));
	else if (size >= getsize)
		return (ft_p3(size));
	else
		return (NULL);
}
