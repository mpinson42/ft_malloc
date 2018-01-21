/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 15:38:57 by mpinson           #+#    #+#             */
/*   Updated: 2017/11/05 17:29:26 by mpinson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include "libft.h"
# include <sys/mman.h>
# include <sys/resource.h>

# define TINY_SIZE 0.25
# define SMALL_SIZE 100
# define PRE_ALLOC 1024
# define MAX_ALLOC 4096

typedef	struct		s_tiny
{
	void			*tab[PRE_ALLOC];
	int				alloc[PRE_ALLOC + 1];
	int				size[PRE_ALLOC];
	char			*plage;
	int				nb_alloc;
	void			*plage_max;
	void			*tab_max[MAX_ALLOC];
	int				alloc_max[MAX_ALLOC + 1];
	int				size_max[MAX_ALLOC];
}					t_tiny;

typedef	struct		s_small
{
	void			*tab[PRE_ALLOC];
	int				alloc[PRE_ALLOC + 1];
	int				size[PRE_ALLOC];
	char			*plage;
	int				nb_alloc;
	void			*plage_max;
	void			*tab_max[MAX_ALLOC];
	int				alloc_max[MAX_ALLOC + 1];
	int				size_max[MAX_ALLOC];
}					t_small;

typedef	struct		s_large
{
	void			*tab[PRE_ALLOC];
	int				alloc[PRE_ALLOC + 1];
	int				size[PRE_ALLOC];
}					t_large;

typedef struct		s_env
{
	int				getsize;
	t_small			small;
	t_tiny			tiny;
	t_large			large;
	int				erreur;
}					t_env;

t_env g_env;

void				ft_free(void *ptr);
void				*ft_realloc(void *ptr, size_t size);
void				*ft_malloc(size_t size);
void				free(void *ptr);
void				*realloc(void *ptr, size_t size);
void				*malloc(size_t size);
void				show_alloc_mem();
void				ft_init(int getsize);
int					free_p2_2(void *ptr, int getsize);

#endif
