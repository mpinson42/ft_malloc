/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 15:37:56 by mpinson           #+#    #+#             */
/*   Updated: 2017/05/19 15:37:58 by mpinson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void ft_init(t_env *env, int getsize)
{
	env->ting_plage = mmap(NULL, (getsize * TINY_SIZE) * MAX_ALLOC, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	env->tiny_start = env->ting_plage;
	env->tiny_end = env->tiny_start + (getsize * TINY_SIZE) * MAX_ALLOC;
	env->small_plage = mmap(NULL, (getsize * SMALL_SIZE) * MAX_ALLOC, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	env->small_start = env->small_plage;
	env->small_end = env->small_start + (getsize * SMALL_SIZE) * MAX_ALLOC;
	env->size_tiny = 0;
	env->size_small = 0;
	env->size_large = 0;
	ft_bzero(env->small, MAX_ALLOC);
	ft_bzero(env->tiny, MAX_ALLOC);
	ft_bzero(env->small_alloc, MAX_ALLOC);
	ft_bzero(env->tiny_alloc, MAX_ALLOC);
	ft_bzero(env->size, MAX_ALLOC);
	ft_bzero(env->libre, MAX_ALLOC);
	ft_bzero(env->large_plage, MAX_ALLOC);
}

void *ft_p1(size_t size, int getsize)
{
	void *str;
	int i;

	i = 0;
	if(env.size_tiny >= MAX_ALLOC)
		return (NULL);
	while(env.tiny[i] != 0)
		i++;
	env.tiny[i] = 1;
	env.tiny_alloc[i] = size;
	str = env.tiny_start + (i * (getsize * TINY_SIZE));
	env.size_tiny++;
	return(str);	
}

void *ft_p2(size_t size, int getsize)
{
	void *str;
	int i;

	i = 0;
	if(env.size_small >= MAX_ALLOC)
		return (NULL);
	while(env.small[i] != 0)
		i++;
	env.small[i] = 1;
	env.small_alloc[i] = size;
	str = env.small_start + (i * (getsize * SMALL_SIZE));
	env.size_small++;
	return(str);	
}

void *ft_p3(size_t size, int getsize)
{
	void *str;
	int i;

	i = 0;
	if(env.size_large >= MAX_ALLOC)
		return (NULL);

	str = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	while(env.libre[i] != 0)
	{
		i++;
	}
	env.libre[i] = 1;
	env.size[i] = size;
	env.large_plage[i] = str;
	return(str);	
}

void *ft_malloc(size_t size)
{
	void *str;
	int getsize;
	static int i = 1;

	getsize = getpagesize();
	if(i == 1)
		ft_init(&env, getsize);
	i = 0;
	if(size <= 0)
		return (NULL);
	else if (size >= 1 && size <= getsize * TINY_SIZE)
		str = ft_p1(size, getsize);
	else if (size >= getsize * TINY_SIZE + 1 && size <= getsize * SMALL_SIZE)
		str = ft_p2(size, getsize);
	else
		str = ft_p3(size, getsize);
	return(str);
}

int main()
{
	char	*str;
	int		i = 0;
	rlim_t s;



	if(!(str = (char *)ft_malloc(sizeof(char) * 1000)))
		return(0);
	str[0] = '!';
	str[1] = 'f';
	if(!(str = (char *)ft_malloc(sizeof(char) * 1000)))
		return(0);
	if(!(str = (char *)ft_malloc(sizeof(char) * 1000)))
		return(0);
	if(!(str = (char *)ft_malloc(sizeof(char) * 1000)))
		return(0);
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
}
