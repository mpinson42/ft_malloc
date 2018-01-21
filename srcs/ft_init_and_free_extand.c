/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_and_free_extand.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 15:50:03 by mpinson           #+#    #+#             */
/*   Updated: 2018/01/21 15:50:11 by mpinson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		free_p2_2(void *ptr, int getsize)
{
	int i;

	i = -1;
	while (++i < MAX_ALLOC)
	{
		if (g_env.small.alloc_max[i] == 1 && g_env.small.tab_max[i] >= ptr &&
			ptr <= g_env.small.tab_max[i] + g_env.small.size_max[i])
		{
			g_env.small.alloc_max[i] = -1;
			g_env.small.size_max[i] = 0;
			g_env.small.tab_max[i] = NULL;
			return (-1);
		}
	}
	return (0);
}

void	ft_init_1(int getsize)
{
	int i;

	i = -1;
	while (++i < PRE_ALLOC)
	{
		g_env.tiny.tab[i] = g_env.tiny.plage + (int)(getsize * 0.25 * i);
		g_env.tiny.alloc[i] = -1;
		g_env.tiny.size[i] = 0;
	}
	i = -1;
	while (++i < PRE_ALLOC)
	{
		g_env.small.tab[i] = g_env.small.plage + (int)(getsize * i);
		g_env.small.alloc[i] = -1;
		g_env.small.size[i] = 0;
	}
	i = -1;
	while (++i < PRE_ALLOC)
	{
		g_env.large.alloc[i] = -1;
		g_env.large.size[i] = 0;
	}
}

void	ft_init(int getsize)
{
	int i;

	g_env.erreur = 0;
	g_env.tiny.nb_alloc = 100;
	g_env.small.nb_alloc = 100;
	g_env.tiny.plage = mmap(NULL, getsize * 0.25 * PRE_ALLOC,
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	g_env.small.plage = mmap(NULL, getsize * PRE_ALLOC,
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	ft_init_1(getsize);
	i = -1;
	while (++i < MAX_ALLOC)
	{
		g_env.small.tab_max[i] = NULL;
		g_env.tiny.tab_max[i] = NULL;
		g_env.tiny.alloc_max[i] = -1;
		g_env.tiny.size_max[i] = 0;
		g_env.small.alloc_max[i] = -1;
		g_env.small.size_max[i] = 0;
	}
	g_env.tiny.alloc[PRE_ALLOC] = 0;
	g_env.small.alloc[PRE_ALLOC] = 0;
	g_env.large.alloc[PRE_ALLOC] = 0;
}
