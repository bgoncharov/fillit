#include "fillit.h"

void    solve_game(t_term	*tetriminos, int i)
{
    t_board board;
    int     size;
    int     j;
    int     k;

    j = 0;
    while (j < 12)
    {
        k = 0;
        while (k < 13)
        {
            board.s[j][k] = '.';
            k++;
        }
        board.s[j][k] = '\0';
        j++;
    }
}