NAME = fillit

CFLAGS = -Wall -Werror -Wextra

SRC = parser.c main.c

OBJS = *.o

$(NAME): lib $(OBJS)
	gcc $(CFLAGS) -o $(NAME) $(OBJS) -L libft -lft

$(OBJS):
	gcc $(CFLAGS) -c $(SRC) -I/ -Ilibft/

all: $(NAME)

lib:
	make -C libft

clean:
	/bin/rm -f $(OBJS)
	make -C libft clean

fclean: clean
	/bin/rm $(NAME)
	make -C libft fclean

re:
	fclean all