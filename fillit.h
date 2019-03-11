#ifndef FILLIT_H
# define FILLIT_H

# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct  s_piece
{
    int x;
    int y;
    int weidh;
    int heigh;
    char **map;
    char letter;
    struct s_piece *next;
}               t_piece;

typedef struct  s_game
{
    t_piece *pieces;
    int nb_pieces;
    int size;
    char **map;
}               t_game;

#endif