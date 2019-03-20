NAME = fillit

FLAGS = -Wall -Werror -Wextra

SRC = main.c board.c checker.c fillit.c tetrimino.c

OBJS = *.o

all: $(NAME)

$(NAME): lib
	gcc $(FLAGS) -o $(NAME) -I./libft -L./libft -lft -o fillit $(SRC)

lib:
	make -C libft

clean:
	/bin/rm -rf $(OBJS)
	make -C libft/ clean

fclean: clean
	/bin/rm -rf $(NAME)
	make -C libft/ fclean

re: fclean all
