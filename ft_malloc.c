#include "malloc.h"

void ft_init(t_env *env, int getsize)
{
	env->ting_plage = mmap(NULL, (getsize * TINY_SIZE) * 100, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	env->tiny_start = env->ting_plage;
	env->tiny_end = env->tiny_start + (getsize * TINY_SIZE) * 100;
	env->small_plage = mmap(NULL, (getsize * SMALL_SIZE) * 100, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	env->small_start = env->small_plage;
	env->small_end = env->small_start + (getsize * SMALL_SIZE) * 100;
	env->size_tiny = 0;
	env->size_small = 0;
	env->size_large = 0;
	ft_bzero(env->small, 100);
	ft_bzero(env->tiny, 100);
}

void *ft_p1(size_t size, int getsize)
{
	void *str;
	int i;

	i = 0;
	if(env.size_tiny >= 100)
		return (NULL);
	while(env.tiny[i] != 0)
		i++;
	env.tiny[i] = 1;
	str = env.tiny_start + (i * (getsize * TINY_SIZE));
	env.size_tiny++;
	return(str);	
}

void *ft_p2(size_t size, int getsize)
{
	void *str;
	int i;

	i = 0;
	if(env.size_small >= 100)
		return (NULL);
	while(env.small[i] != 0)
		i++;
	env.small[i] = 1;
	str = env.small_start + (i * (getsize * SMALL_SIZE));
	env.size_small++;
	return(str);	
}

void *ft_p3(size_t size, int getsize)
{
	void *str;
	if(env.size_large >= 100)
		return (NULL);

	str = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
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



	if(!(str = (char *)ft_malloc(sizeof(char) * 100000000)))
		return(0);
	if(!(str = (char *)ft_malloc(sizeof(char) * 100000000)))
		return(0);
	if(!(str = (char *)ft_malloc(sizeof(char) * 100000000)))
		return(0);
	if(!(str = (char *)ft_malloc(sizeof(char) * 100000000)))
		return(0);
	while (i<500)
		str[i++] = 'o';

	ft_putstr(str);
	ft_free(str);
	while(1);
	return(0);
}