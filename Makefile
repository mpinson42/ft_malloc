ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

SRC = ./srcs/ft_malloc.c ./srcs/ft_free.c ./srcs/ft_realloc.c ./srcs/show_alloc_mem.c ./srcs/ft_init_and_free_extand.c

FLAGS = -Wall -Wextra -Werror

SRC2 = ./ft_malloc.o ./ft_free.o ./ft_realloc.o ./show_alloc_mem.o

all: $(NAME)

%.o : %.c
	gcc -c -o $@ $^

$(NAME): $(SRC)
	@echo "mpinson" > auteur
	@make -C ./libft all
	@cp ./libft/libft.a ./lib
	gcc -shared -I ./include/ -L ./lib -lft -o $(NAME) $(SRC)
	ln -s $(NAME) libft_malloc.so


clean:
	/bin/rm -f $(SRC2)
	/bin/rm -f libft_malloc.so
	@make -C ./libft clean

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f libft_malloc.so
	@make -C ./libft fclean

re: fclean all
