/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 15:38:09 by mpinson           #+#    #+#             */
/*   Updated: 2017/05/19 15:38:11 by mpinson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void *rea_p1(void *ptr, int getsize, size_t size)
{
	void *str;
	int i;

	if (size >= 1 && size <= getsize * TINY_SIZE)
	{
		i = 0;
		while(env.tiny_start + ((getsize * TINY_SIZE) * i) != ptr)
			i++;
		env.tiny_alloc[i] = size;
		return (ptr);
	}
	str = ft_malloc(size);
	ft_memcpy(str, ptr, ft_strlen(ptr));
	ft_free(ptr);
	return(str);
}

void *rea_p2(void *ptr, int getsize, size_t size)
{
	void *str;
	int i;

	if (size >= 1 && size <= getsize * SMALL_SIZE)
	{
		i = 0;
		while(env.small_start + ((getsize * SMALL_SIZE) * i) != ptr)
			i++;
		env.small_alloc[i] = size;
		return (ptr);
	}
	str = ft_malloc(size);
	ft_memcpy(str, ptr, ft_strlen(ptr));
	ft_free(ptr);
	return(str);
}

void *rea_p3(void *ptr, int getsize, size_t size)
{
	void *str;

	str = ft_malloc(size);
	ft_memcpy(str, ptr, ft_strlen(ptr));
	ft_free(ptr);
	return(str);
}


void *ft_realloc(void *ptr, size_t size)
{
	int getsize;
	void *str;

	getsize = getpagesize();
	if(ptr >= env.tiny_start && ptr <= env.tiny_end)
		str = rea_p1(ptr, getsize, size);
	else if(ptr >= env.small_start && ptr <= env.small_end)
		str = rea_p2(ptr, getsize, size);
	else
		str = rea_p3(ptr, getsize, size);
	return (str);
}
