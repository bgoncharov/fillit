NAME = fillit

SRC = 
OBJ = 

$(NAME): lib $(OBJS)
	gcc -Wall -Werror -Wextra -o $(NAME) $(OBJ) -L libft -lft

all: $(NAME)

lib:
	make -C libft

clean:
	/bin/rm -f $(OBJ)
	make -C libft clean

fclean: clean
	/bin/rm 
	make -C libft fclean

re:
	fclean all