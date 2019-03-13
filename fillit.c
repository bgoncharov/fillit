#include "fillit.h"
#include <stdio.h>

void    init_board(t_board *board)
{
    int     j;
    int     k;

    j = 0;
    while (j < 12)
    {
        k = 0;
        while (k < 12)
        {
            board->s[j][k] = '.';
            k++;
        }
        board->s[j][k] = '\n';
        board->s[j][k + 1] = '\0';
        j++;
    }
}

void    print_board(t_board *board)
{
    int     j;
    int     k;

    j = 0;
    while (j < 12)
    {
        k = 0;
        while (k <= 12)
        {
            printf("%c", board->s[j][k]);
            k++;
        }
        j++;
    }
}

void    solve_game(t_term	*tetriminos, int count)
{
    t_board board;
    int     size;
    int     i;
    int     j;
    //int     k;

    size = count * 4 / 2 + 1;
    i = 0;
    board.x = 0;
    init_board(&board);
    print_board(&board);
    printf("\n");
    while (i < 4)
    {
        printf("first\n");
        j = 0;
        board.y = 0;
        while (j < 4)
        {
            printf("second\n");
            if (board.s[board.x][board.y] == '.' && tetriminos[0].line[i][j] != '.')
            {
                board.s[board.x][board.y] = tetriminos[0].line[i][j];
                if (tetriminos[0].line[i][j + 1] == '.')
                    board.x++;
                board.y++;
            }
            j++;
        }
        i++;
    }
    print_board(&board);
}