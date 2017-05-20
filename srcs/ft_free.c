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

static void	free_p1(void *ptr, int getsize)
{
	void	*tmp;
	int		i;

	i = 0;
	tmp = ptr;
	munmap(ptr, getsize * TINY_SIZE);
	ptr = mmap(tmp, getsize * TINY_SIZE, PROT_READ | PROT_EXEC |
		PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	while (g_env.tiny_start + ((getsize * TINY_SIZE) * i)
		!= ptr && g_env.small_start != ptr)
		i++;
	g_env.tiny[i] = 0;
	g_env.tiny_alloc[i] = 0;
	g_env.size_tiny--;
}

static void	free_p2(void *ptr, int getsize)
{
	void	*tmp;
	int		i;

	i = 0;
	tmp = ptr;
	munmap(ptr, getsize * SMALL_SIZE);
	ptr = mmap(tmp, getsize * SMALL_SIZE, PROT_READ | PROT_EXEC |
		PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	while (g_env.small_start + ((getsize * SMALL_SIZE) * i)
		!= ptr && g_env.small_start != ptr)
		i++;
	g_env.small[i] = 0;
	g_env.small_alloc[i] = 0;
	g_env.size_small--;
}

static void	free_p3(void *ptr, int getsize)
{
	int i;

	i = 0;
	while (g_env.large_plage[i] != ptr)
		i++;
	g_env.libre[i] = 0;
	g_env.size[i] = 0;
	g_env.large_plage[i] = 0;
	munmap(ptr, ft_strlen(ptr));
}

void		free(void *ptr)
{
	int getsize;

	getsize = getpagesize();
	if (ptr >= g_env.tiny_start && ptr <= g_env.tiny_end)
		free_p1(ptr, getsize);
	else if (ptr >= g_env.small_start && ptr <= g_env.small_end)
		free_p2(ptr, getsize);
	else
		free_p3(ptr, getsize);
}
