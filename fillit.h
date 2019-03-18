#ifndef FILLIT_H
# define FILLIT_H

# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

int				read_file(char *file, int fd);

typedef struct	s_term
{
	int		x;
	int		y;
	int		height;
	int		width;
	char	letter;//?
	char	line[4][5];
}				t_term;

typedef struct	s_board
{
	int		x;
	int		y;
	char s[12][13];
}				t_board;

void    solve_game(t_term	*tet, int i);
void    init_board(t_board *board, int size);
void    print_board(t_board *board, int size);

#endif