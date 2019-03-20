#ifndef FILLIT_H
# define FILLIT_H

# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

int				read_file(char *file, int fd);

typedef struct	s_term
{
	int				x;
	int				y;
	int				height;
	int				width;
	char			letter;
	char			line[4][5];
	struct s_term	*next;
}					t_term;

typedef struct	s_board
{
	t_term		*tetrs;
	int			x;
	int			y;
	int			nbr;
	char		s[12][13];
}				t_board;

void	solve_game(t_board *board);
void	init_board(t_board *board, int size);
void	print_board(t_board *board, int size);
int		min_size(int count);
int		check_tet(char *buf, int i);
int		check_block(char *buf);
void	get_param(t_term	*tet, char *buf);
void	move_tet(t_term	*tet);
t_term	*create_tet(char *buf);
void	pushback(t_board *board, t_term *tet);
int		read_file(char *file, int fd);
void	set_piece(t_board *board, t_term *tet, char c);
int		place(t_board *board, t_term *tet);
int		check_solve(t_board *board, t_term *tet, int size, int count);

#endif
