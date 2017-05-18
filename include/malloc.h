#ifndef MALLOC_H
# define MALLOC_H

#include "libft.h"
#include <sys/mman.h>
#include <sys/resource.h>

#define TINY_SIZE 2
#define SMALL_SIZE 4

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
	int tiny[100];
	void *ting_plage;
	int size_tiny;


	void *small_start;
	void *small_end;
	int small[100];
	void *small_plage;
	int size_small;


	struct s_large large[100];
	void *large_plage[100];
	int	size_large;
}				t_env;

t_env env;

void ft_free(void *ptr);

#endif