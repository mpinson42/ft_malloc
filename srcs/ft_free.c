/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 15:37:29 by mpinson           #+#    #+#             */
/*   Updated: 2017/05/19 15:37:41 by mpinson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int	free_p1_2(void *ptr, int getsize)
{
	int i;

	i = -1;
	while (++i < MAX_ALLOC)
	{
		if (g_env.tiny.alloc_max[i] == 1 && g_env.tiny.tab_max[i] >= ptr &&
			ptr <= g_env.tiny.tab_max[i] + g_env.tiny.size_max[i])
		{
			g_env.tiny.alloc_max[i] = -1;
			g_env.tiny.size_max[i] = 0;
			g_env.tiny.tab_max[i] = NULL;
			return (-1);
		}
	}
	return (0);
}

static int	free_p1(void *ptr, int getsize)
{
	void	*tmp;
	int		i;

	i = -1;
	while (++i < PRE_ALLOC)
	{
		if (g_env.tiny.alloc[i] == 1 && g_env.tiny.tab[i] >= ptr &&
			ptr < g_env.tiny.tab[i] + g_env.tiny.size[i])
		{
			g_env.tiny.alloc[i] = -1;
			g_env.tiny.size[i] = 0;
			g_env.small.tab[i] = NULL;
			return (-1);
		}
	}
	return (free_p1_2(ptr, getsize));
}

static int	free_p2(void *ptr, int getsize)
{
	void	*tmp;
	int		i;

	i = -1;
	while (++i < PRE_ALLOC)
	{
		if (g_env.small.alloc[i] == 1 && g_env.small.tab[i] >= ptr &&
			ptr < g_env.small.tab[i] + (int)(getsize))
		{
			g_env.small.alloc[i] = -1;
			g_env.small.size[i] = 0;
			g_env.small.tab[i] = NULL;
			return (-1);
		}
	}
	return (free_p2_2(ptr, getsize));
}

static int	free_p3(void *ptr, int getsize)
{
	void	*tmp;
	int		i;

	i = -1;
	while (++i < PRE_ALLOC)
	{
		if (g_env.large.alloc[i] == 1 && g_env.large.tab[i] >= ptr &&
			ptr <= g_env.large.tab[i] + g_env.large.size[i])
		{
			munmap(g_env.large.tab[i], g_env.large.size[i]);
			g_env.large.alloc[i] = -1;
			g_env.large.size[i] = 0;
			g_env.large.tab[i] = NULL;
			return (-1);
		}
	}
	return (0);
}

void		free(void *ptr)
{
	int getsize;

	getsize = getpagesize();
	if (ptr == NULL)
		return ;
	if (free_p1(ptr, getsize) == -1)
		return ;
	else if (free_p2(ptr, getsize) == -1)
		return ;
	else if (free_p3(ptr, getsize) == -1)
		return ;
	g_env.erreur++;
}
