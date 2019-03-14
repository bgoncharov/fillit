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

int put_on_board(t_board *board, t_term *tetriminos, int id, int x, int y)
{
    int i;//?
    int j;
    int start;

    j = 0;
    start = 1;

    if (board->s[y][x] != '.' && tetriminos[id].line[0][0] != '.')
        return (0);
    while (start && j < tetriminos[id].height)
    {
        i = 0;
        while (start && i < tetriminos[id].width)
        {
            if (board->s[y + j][x + i] != '.'
                && tetriminos[id].line[j][i] != '.')
                start = 0;
            else if (board->s[y + j][x + i] == '.')
            {
                board->s[y + j][x + i] = tetriminos[id].line[j][i];
                printf("%c", board->s[y + j][x + i]);
            }
            i = (start) ? i + 1 : i;
        }
        j = (start) ? j + 1 : j;
    }
    printf("\n");
    if (start)
        return (1);
    return (0);//fake_func(board, tetrmino, i, j));
}

int check_solve(t_board *board, t_term *tetriminos, int size, int id, int count)
{
    int x;
    int y;
    

   /* if (!tetrimino)
        return (0); */
    x = 0;
    y = 0;
    //printf("id = %d\n", id);
    while (y + tetriminos[id].height <= size && id < count)
    {
        x = 0;
        while (x + tetriminos[id].width <= size && id < count)
        {
            if (put_on_board(board, tetriminos, id, x, y))
            {
                if (id == count - 1)
                    return (1);
                id++;
                if (check_solve(board, tetriminos, size, id, count))
                    return (1);
                /*else
                    fake_func();*/
            }
            x++;
        }
       y++;
    }
    return (0);
}

void    solve_game(t_term	*tetriminos, int id)
{
    t_board board;
    int     size;
    int     h;
    int     w;
    int     count;

    printf("id = %d\n", id);
    count = id + 1;
    size = (id + 1) * 4 / 2 + 1;
    init_board(&board);
    print_board(&board);
    printf("\n");
    h = tetriminos[id].height;
    w = tetriminos[id].width;


    while (!check_solve(&board, tetriminos, size, id, count) && size <= 12)
    {
        printf("size = %d\n", size);
        size++;
        init_board(&board);    
    }
    print_board(&board);
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

    print_board(&board);*/
}
