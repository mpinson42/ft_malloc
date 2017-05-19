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

void free_p1(void *ptr, int getsize)
{
	void *tmp;
	int i;

	ft_putstr("HAlors");
	i = 0;
	tmp = ptr;
	munmap(ptr, getsize * TINY_SIZE);
	ptr = mmap(tmp, getsize * TINY_SIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	while(env.tiny_start + ((getsize * TINY_SIZE) * i) != ptr && env.small_start != ptr)
		i++;
	env.tiny[i] = 0;
	env.tiny_alloc[i] = 0;
	env.size_tiny--;
}

void free_p2(void *ptr, int getsize)
{
	void *tmp;
	int i;

	ft_putstr("HA");
	i = 0;
	tmp = ptr;
	munmap(ptr, getsize * SMALL_SIZE);
	ptr = mmap(tmp, getsize * SMALL_SIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	while(env.small_start + ((getsize * SMALL_SIZE) * i) != ptr && env.small_start != ptr)
		i++;
	env.small[i] = 0;
	env.small_alloc[i] = 0;
	env.size_small--;

}

void free_p3(void *ptr, int getsize)
{
	int i;

	i = 0;
	while(env.large_plage[i] != ptr)
	{
		i++;
	}
	env.libre[i] = 0;
	env.size[i] = 0;
	env.large_plage[i] = 0;
	munmap(ptr, ft_strlen(ptr));
	ft_putstr("non");
}

void ft_free(void *ptr)
{
	int getsize;

	getsize = getpagesize();
	if(ptr >= env.tiny_start && ptr <= env.tiny_end)
		free_p1(ptr, getsize);
	else if(ptr >= env.small_start && ptr <= env.small_end)
		free_p2(ptr, getsize);
	else
		free_p3(ptr, getsize);

}
