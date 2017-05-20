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

static void	ft_init(t_env *g_env, int getsize)
{
	g_env->ting_plage = mmap(NULL, (getsize * TINY_SIZE) * MAX_ALLOC +
			(getsize * SMALL_SIZE) * MAX_ALLOC, PROT_READ | PROT_WRITE |
			PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	g_env->tiny_start = g_env->ting_plage;
	g_env->tiny_end = g_env->tiny_start + (getsize * TINY_SIZE) * MAX_ALLOC;
	g_env->small_plage = g_env->ting_plage + (getsize * SMALL_SIZE) * MAX_ALLOC;
	g_env->small_start = g_env->small_plage;
	g_env->small_end = g_env->small_start + (getsize * SMALL_SIZE) * MAX_ALLOC;
	g_env->size_tiny = 0;
	g_env->size_small = 0;
	g_env->size_large = 0;
	ft_bzero(g_env->small, MAX_ALLOC);
	ft_bzero(g_env->tiny, MAX_ALLOC);
	ft_bzero(g_env->small_alloc, MAX_ALLOC);
	ft_bzero(g_env->tiny_alloc, MAX_ALLOC);
	ft_bzero(g_env->size, MAX_ALLOC);
	ft_bzero(g_env->libre, MAX_ALLOC);
	ft_bzero(g_env->large_plage, MAX_ALLOC);
}

static void	*ft_p1(size_t size, int getsize)
{
	void	*str;
	int		i;

	i = 0;
	if (g_env.size_tiny >= MAX_ALLOC)
		return (NULL);
	while (g_env.tiny[i] != 0)
		i++;
	g_env.tiny[i] = 1;
	g_env.tiny_alloc[i] = size;
	str = g_env.tiny_start + (i * (getsize * TINY_SIZE));
	g_env.size_tiny++;
	return (str);
}

static void	*ft_p2(size_t size, int getsize)
{
	void	*str;
	int		i;

	i = 0;
	if (g_env.size_small >= MAX_ALLOC)
		return (NULL);
	while (g_env.small[i] != 0)
		i++;
	g_env.small[i] = 1;
	g_env.small_alloc[i] = size;
	str = g_env.small_start + (i * (getsize * SMALL_SIZE));
	g_env.size_small++;
	return (str);
}

static void	*ft_p3(size_t size, int getsize)
{
	void	*str;
	int		i;

	i = 0;
	if (g_env.size_large >= MAX_ALLOC)
		return (NULL);
	str = mmap(NULL, size, PROT_READ | PROT_WRITE | PROT_EXEC,
			MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	while (g_env.libre[i] != 0)
		i++;
	g_env.libre[i] = 1;
	g_env.size[i] = size;
	g_env.large_plage[i] = str;
	return (str);
}

void		*malloc(size_t size)
{
	void		*str;
	int			getsize;
	static int	i = 1;

	getsize = getpagesize();
	if (i == 1)
		ft_init(&g_env, getsize);
	i = 0;
	if (size <= 0)
		return (NULL);
	else if (size >= 1 && size <= getsize * TINY_SIZE)
		str = ft_p1(size, getsize);
	else if (size >= getsize * TINY_SIZE + 1 &&
			size <= getsize * SMALL_SIZE)
		str = ft_p2(size, getsize);
	else
		str = ft_p3(size, getsize);
	return (str);
}
/*
int		main()
{
	char	*str;
	int		i;

	i = 0;
	if (!(str = (char *)ft_malloc(sizeof(char) * 1000)))
		return (0);
	str[0] = '!';
	str[1] = 'f';
	if (!(str = (char *)ft_malloc(sizeof(char) * 1000)))
		return (0);
	if (!(str = (char *)ft_malloc(sizeof(char) * 1000)))
		return(0);
	if (!(str = (char *)ft_malloc(sizeof(char) * 1000)))
		return (0);
	while (i<500)
		str[i++] = 'o';
	str = ft_realloc(str, sizeof(char) * 100000000);
	while (i<1000)
		str[i++] = 'd';
	ft_putstr(str);
	ft_free(str);
	ft_putstr("\n");
	show_alloc_mem();
	return(0);
}*/
