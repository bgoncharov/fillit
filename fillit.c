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

int put_on_board(t_board *board, t_term *tetrmino)
{
    int i;
    int j;
    int start;

    j = 0;
    start = 1;
    if (board->s[tetrmino->x][tetrmino->y] != '.' && tetrmino->line[0][0] != '.')
        return (0);
    while (start && j < tetrmino->heigh)
    {
        i = 0;
        while (start && i < tetrmino->width)
        {
            if (board->s[tetrmino->y + j][tetrmino->x + i] != '.'
                && tetrmino->line[j][i] != '.')
                start = 0;
            else if (board->s[tetrmino->y + j][tetrmino->x + i] == '.')
                board->s[tetrmino->y + j][tetrmino->x + i] = tetrmino->line[j][i];
            i = start ? i + 1 : i;
        }
        j = start ? j + 1 : j;
    }
    if (start)
        return (1);
    return (fake_func(board, tetrmino, i, j));
}

int check_solve(t_board *board, t_term *tetrimino, int size, int count)
{
    int i;

    if (!tetrimino)
        return (0);
    tetrimino->x = 0;
    tetrimino->y = 0;
    while (tetrimino->y + tetrimino->width <= size)
    {
        i = 0;
        while (tetrimino->x + tetrimino->width <= size)
        {
            if (put_on_board(board, tetrimino))
            {
                if (check_solve(board, tetrimino[i]))
                    return (1);
                else
                    fake_func();
            }
            i++;
            tetrimino->x++;
        }
        tetrimino->y++;
    }
    return (0);
}

void    solve_game(t_term	*tetriminos, int count)
{
    t_board *board; //put pointer
    int     size;
    int     i;
    int     j;
    //int     k;

    size = count * 4 / 2 + 1;
    i = 0;
    board->x = 0; //
    init_board(&board);
    print_board(&board);
    printf("\n");

    while (!check_solve(board, tetriminos, size, count))
    {
        size++;
        j = 0;
        while (j < size);
            /*....*/
    }
    
    /*while (i < 4)
    {
        j = 0;
        board.y = 0;
        while (j < 4)
        {
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