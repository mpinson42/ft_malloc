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

static int	free_p1(void *ptr, int getsize)
{
	void	*tmp;
	int		i;

	i = 0;
	while(i < PRE_ALLOC)
	{
		if(g_env.tiny.alloc[i] == 1 && g_env.tiny.tab[i] >= ptr && ptr < g_env.tiny.tab[i] + (int)(getsize * 0.5))
		{
		//	printf("free1\n");
//			munmap(g_env.tiny.tab[i], g_env.tiny.size[i]);
//			g_env.tiny.tab[i] = mmap(NULL, getsize * 0.5, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
			g_env.tiny.alloc[i] = -1;
			g_env.tiny.size[i] = 0;
			return(-1);                                
		}
		i++;
	}

	i = 0;
	while(i < MAX_ALLOC)
	{
		if(g_env.tiny.alloc_max[i] == 1 && g_env.tiny.tab_max[i] >= ptr && ptr <= g_env.tiny.tab_max[i] + g_env.tiny.size_max[i])
		{
		//	printf("free2\n");
			munmap(g_env.tiny.tab_max[i], g_env.tiny.size_max[i]);  //gere la size
			g_env.tiny.alloc_max[i] = -1;
			g_env.tiny.size[i] = 0;
			return(-1);                                
		}
		i++;
	}
	return(0);
}

static int	free_p2(void *ptr, int getsize)
{
	void	*tmp;
	int		i;

	i = 0;
	while(i < PRE_ALLOC)
	{
		if(g_env.small.alloc[i] == 1 && g_env.small.tab[i] >= ptr && ptr < g_env.small.tab[i] + (int)(getsize))
		{
		//	printf("non2");
//			munmap(g_env.small.tab[i], g_env.small.size[i] );
//			g_env.small.tab[i] = mmap(NULL, getsize, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
			g_env.small.alloc[i] = -1;
			g_env.small.size[i] = 0;
			return(-1);                                
		}
		i++;
	}
	i = 0;
	while(i < MAX_ALLOC)
	{
		if(g_env.small.alloc_max[i] == 1 && g_env.small.tab_max[i] >= ptr && ptr <= g_env.small.tab_max[i] + g_env.small.size_max[i])
		{
		//	printf("free2\n");
			munmap(g_env.small.tab_max[i], g_env.small.size_max[i]);  //gere la size
			g_env.small.alloc_max[i] = -1;
			g_env.small.size[i] = 0;
			return(-1);                                
		}
		i++;
	}
	return(0);
}

static int	free_p3(void *ptr, int getsize)
{
	void	*tmp;
	int		i;

	i = 0;
	while(i < PRE_ALLOC)
	{
		if(g_env.large.alloc[i] == 1 && g_env.large.tab[i] >= ptr && ptr <= g_env.large.tab[i] + g_env.large.size[i])
		{
		//	printf("free2\n");
			munmap(g_env.large.tab[i], g_env.large.size[i]);  //gere la size
			g_env.large.alloc[i] = -1;
			g_env.large.size[i] = 0;
			return(-1);                                
		}
		i++;
	}
	return(0);
}

void		free(void *ptr)
{
	int getsize;

	getsize = getpagesize();
	if (free_p1(ptr, getsize) == -1)
		return ;
	else if (free_p2(ptr, getsize) == -1)
		return ;
	else if(free_p3(ptr, getsize) == -1)
		return ;
//	printf("pointer being freed was not allocated");
//	exit(-1);
}
