#ifndef FILLIT_H
# define FILLIT_H

# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct		s_term
{
	int				x;
	int				y;
	int				height;
	int				width;
	char			letter;
	char			line[4][5];
	struct s_term	*next;
}					t_term;

typedef struct		s_board
{
	t_term			*tetrs;
	int				x;
	int				y;
	int				nbr;
	char			s[12][13];
}					t_board;

int					ft_error(void);
int					read_file(char *file, int fd, t_board *board);
void				solve_game(t_board *board);
void				init_board(t_board *board, int size);
void				print_board(t_board *board, int size);
int					min_size(int count);
int					check_tet(char *buf, int i);
int					check_block(char *buf);
void				get_tet(t_board *board, char *buf);
void				get_param(t_term	*tet, char *buf);
void				find_coord(t_term	*tet);
void				move_up(t_term *tet, int x);
void				move_left(t_term *tet, int y);
t_term				*create_tet(char *buf);
void				pushback(t_board *board, t_term *tet);
void				set_piece(t_board *board, t_term *tet, char c);
int					place(t_board *board, t_term *tet);
int					check_solve(t_board *board, t_term *tet, int size, int count);//delete count

#endif
