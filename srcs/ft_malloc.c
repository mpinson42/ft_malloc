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

static void	ft_init(int getsize)
{
	int i;

	g_env.tiny.alloc[PRE_ALLOC] = 0;
	g_env.small.alloc[PRE_ALLOC] = 0;
	g_env.large.alloc[PRE_ALLOC] = 0;
	g_env.erreur = 0;
	g_env.tiny.nb_alloc = 100;
	g_env.small.nb_alloc = 100;
	g_env.tiny.plage = mmap(NULL, getsize * 0.25 * PRE_ALLOC, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	g_env.small.plage = mmap(NULL, getsize * PRE_ALLOC, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	i = 0;
	while(i < PRE_ALLOC)
	{
		g_env.tiny.tab[i] = g_env.tiny.plage +  (int)(getsize * 0.25 * i);
		g_env.tiny.alloc[i] = -1;
		g_env.tiny.size[i] = 0;
		i++;
	}
	i = 0;
	while(i < PRE_ALLOC)
	{
		g_env.small.tab[i] = g_env.small.plage +  (int)(getsize * i);
		g_env.small.alloc[i] = -1;
		g_env.small.size[i] = 0;
		i++;
	}
	i = 0;
	while(i < PRE_ALLOC)
	{
		//g_env.large.tab[i] = mmap(NULL, getsize * 2, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		g_env.large.alloc[i] = -1;
		g_env.large.size[i] = 0;
		i++;
	}

	i = 0;
	while(i < MAX_ALLOC)
	{
		g_env.small.tab_max[i] = NULL;
		g_env.tiny.tab_max[i] = NULL;
		g_env.tiny.alloc_max[i] = -1;
		g_env.tiny.size_max[i] = 0;
		g_env.small.alloc_max[i] = -1;
		g_env.small.size_max[i] = 0;
		i++;
	}
	g_env.tiny.alloc[PRE_ALLOC] = 0;
	g_env.small.alloc[PRE_ALLOC] = 0;
	g_env.large.alloc[PRE_ALLOC] = 0;
}

void *ft_p1(int size)
{
	int i = 0;
	while(g_env.tiny.alloc[i] != 0 && g_env.tiny.alloc[i] != -1)
		i++;

	if(g_env.tiny.alloc[i] == 0)
	{
		i = 0;
		while(g_env.tiny.alloc_max[i] != 1 && g_env.tiny.alloc_max[i] != -1)
			i++;
		if(g_env.tiny.alloc_max[i] == 0)
			return(NULL);
		if(g_env.tiny.nb_alloc % 4 == 0)
			g_env.tiny.tab_max[i] = mmap(g_env.tiny.plage + (int)(getpagesize() * 0.25 * (i + g_env.tiny.nb_alloc)), size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		else
			g_env.tiny.tab_max[i] = g_env.tiny.plage + (int)(getpagesize() * 0.25 * (i + g_env.tiny.nb_alloc));
		g_env.tiny.alloc_max[i] = 1;
		g_env.tiny.size_max[i] = size;
		g_env.tiny.nb_alloc++;
		return(g_env.tiny.tab_max[i]);

	}
	g_env.tiny.alloc[i] = 1;
	g_env.tiny.size[i] = size;
	return(g_env.tiny.tab[i]);
}

void *ft_p2(int size)
{
	int i = 0;

	while(g_env.small.alloc[i] != 0 && g_env.small.alloc[i] != 1)
		i++;
	if(g_env.small.alloc[i] == 0)
	{
		i = 0;
		while(g_env.small.alloc_max[i] != 0 && g_env.small.alloc_max[i] != -1)
			i++;
		if(g_env.small.alloc_max[i] == 0)
			return(NULL);
		g_env.small.tab_max[i] = mmap(g_env.small.plage +  (int)(getpagesize() * (i + g_env.small.nb_alloc))   , size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		g_env.small.alloc_max[i] = 1;
		g_env.small.size_max[i] = size;
		g_env.small.nb_alloc++;
		return(g_env.small.tab_max[i]);
	}
	g_env.small.alloc[i] = 1;
	g_env.small.size[i] = size;
	return(g_env.small.tab[i]);
}

void *ft_p3(int size)
{
	int i = 0;
	while(g_env.large.alloc[i] != 0 && g_env.large.alloc[i] != -1)
		i++;
	//printf("malloc2\n");
	if(g_env.large.alloc[i] == 0)
		return(NULL);
	g_env.large.tab[i] = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	g_env.large.alloc[i] = 1;
	g_env.large.size[i] = size;
	return(g_env.large.tab[i]);
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

	if(size > 0 && size <= getsize * 0.25)
		return(ft_p1(size));
	else if (size > getsize * 0.25 && size < getsize)
		return(ft_p2(size));
	else if (size >= getsize)
		return(ft_p3(size));
	else
		return (NULL);
}
/*
int		main()
{
	char	*str;
	char	*str2;
	int		i;

	i = 0;
	if (!(str = (char *)ft_malloc(sizeof(char) * 1000)))
		return (0);
	str[0] = '!';
	str[1] = 'f';
	
	if (!(str2 = (char *)ft_realloc(str,100000000)))
		return (0);
	str2[0] = '4';
	str2[1] = '2';
	printf("%s\n%s\n", str, str2);
	ft_free(str);
	return(0);
}*/
