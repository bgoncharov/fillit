#ifndef FILLIT_H
# define FILLIT_H

# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

int				read_file(char *file, int fd);

typedef struct	s_term
{
	int		height;
	int		width;
	char	line[4][6];
}				t_term;

typedef struct	s_board
{
	int		x;
	int		y;
	char s[12][13];
}				t_board;

void    solve_game(t_term	*tetriminos, int i);

#endif