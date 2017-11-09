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

static void	*re_p1(void *ptr, int getsize, int size)
{
	void	*tmp;
	int		i;
	void	*str;

	i = 0;
	while(i < PRE_ALLOC)
	{
		if(g_env.tiny.alloc[i] == 1 && g_env.tiny.tab[i] >= ptr && ptr < g_env.tiny.tab[i + 1] + (int)(getsize * 0.5))
		{
			if(size > 0 && size <  (int)(getsize * 0.5))
				return(ptr);
		//	printf("realloc1\n");
			str = (void *)malloc(size);
			ft_memmove(str, ptr, g_env.tiny.size[i]);
			free(ptr);
			return(str);                               
		}
		i++;
	}
	return(NULL);
}

static void	*re_p2(void *ptr, int getsize, int size)
{
	void	*tmp;
	int		i;
	void *str;

	i = 0;
	while(i < PRE_ALLOC)
	{
		if(g_env.small.alloc[i] == 1 && g_env.small.tab[i] >= ptr && ptr < g_env.small.tab[i + 1] + (int)(getsize))
		{
			if(size >= (int)(getsize * 0.5) && size <  (int)(getsize))
				return(ptr);
			str = (void *)malloc(size);
			ft_memmove(str, ptr, g_env.small.size[i]);
			free(ptr);
			return(str);                                
		}
		i++;
	}
	return(NULL);
}

static void	*re_p3(void *ptr, int getsize, int size)
{
	void	*tmp;
	int		i;
	void *str;

	i = 0;
	//printf("%d\n",(g_env.large.tab[i]);
	//ft_putstr(ft_itoa_base((uintmax_t)ptr, 16));
/*	while(i < PRE_ALLOC)
	{
		if(size >= (int)(getsize) && size <  (int)(getsize * 2))
				return(ptr);
		//	printf("malloc2\n");
		if(g_env.large.alloc[i] == 1)
			printf("%p\n",g_env.large.tab[i]);
		if(g_env.large.alloc[i] == 1 && g_env.large.tab[i] >= ptr)
		{*/







			str = (void *)malloc(size);
			ft_memmove(str, ptr, ft_strlen(ptr));                                                  //gere la size
			free(ptr);
			return(str);
	/*	}
		i++;
	}
	ft_putnbr(3);
	ft_putchar('\n');
	return(NULL);*/
}
			//attention||
void		*realloc(void *ptr, size_t size)
{
	int getsize;
	void *str;

	static int count = 0;
	getsize = getpagesize();
	count++;

//	if(ptr == NULL && count > 1)
//		return (NULL);
	/*if ((str = re_p1(ptr, getsize, size)) != NULL)
		return (str);
	else if ((str = re_p2(ptr, getsize, size)) != NULL)
		return (str);

	*/
//	if(ptr == NULL && count > 1)
//		return (NULL);
	if((str = re_p3(ptr, getsize, size)) != NULL)
		return (str);
	return(NULL);
}
