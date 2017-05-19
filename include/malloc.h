/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 15:38:57 by mpinson           #+#    #+#             */
/*   Updated: 2017/05/19 15:38:59 by mpinson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

#include "libft.h"
#include <sys/mman.h>
#include <sys/resource.h>

#define TINY_SIZE 2
#define SMALL_SIZE 4
#define MAX_ALLOC 100

typedef	struct		s_tiny
{
	void			*adress;
	size_t			size;
}					t_tiny;

typedef	struct		s_small
{
	void			*adress;
	size_t			size;
}					t_small;


typedef	struct		s_large
{
	void			*adress;
	size_t			size;
}					t_large;

typedef struct s_env
{
	int getsize;


	void *tiny_start;
	void *tiny_end;
	int tiny[MAX_ALLOC];
	int tiny_alloc[MAX_ALLOC];
	void *ting_plage;
	int size_tiny;


	void *small_start;
	void *small_end;
	int small[MAX_ALLOC];
	int small_alloc[MAX_ALLOC];
	void *small_plage;
	int size_small;


	struct s_large large[MAX_ALLOC];
	void *large_plage[MAX_ALLOC];
	int libre[MAX_ALLOC];
	int size[MAX_ALLOC];
	int	size_large;
}				t_env;

t_env env;

void ft_free(void *ptr);
void *ft_realloc(void *ptr, size_t size);
void *ft_malloc(size_t size);
void show_alloc_mem();

#endif
