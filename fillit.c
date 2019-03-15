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

int revert_board(t_board *board, t_term *tetriminos, int w, int h, int id)
{
    int i;
    int j;

    j = 0;
    if (h > 0)
        w = tetriminos[id].width - 1;
    while (j <= w)
    {
        i = 0;
        while (i <= w)
        {
            if (board->s[tetriminos[id].y + j][tetriminos[id].x + i] == tetriminos[id].line[j][i])
                board->s[tetriminos[id].y + j][tetriminos[id].x + i] = '.';
            i++;
        }
        j++;
    }
    return (0);
}

int put_on_board(t_board *board, t_term *tetriminos, int id)
{
    int i;
    int j;
    int start;

    j = 0;
    start = 1;
    if (board->s[tetriminos[id].y][tetriminos[id].x] != '.' && tetriminos[id].line[0][0] != '.')
        return (0);
    while (start && j <= tetriminos[id].height)
    {
        i = 0;
        while (start && i <= tetriminos[id].width)
        {
            if (board->s[tetriminos[id].y + j][tetriminos[id].x + i] != '.' && tetriminos[id].line[j][i] != '.')
                start = 0;
            else if (board->s[tetriminos[id].y + j][tetriminos[id].x + i] == '.')// && tetriminos[id].line[j][i] != '.')
            {
                board->s[tetriminos[id].y + j][tetriminos[id].x + i] = tetriminos[id].line[j][i];
               // printf("%c\n", board->s[y + j][x + i]);
            }
            if (start) 
                i++;
        }
        if (start) 
            j++;
    }
   // print_board(board);
   // printf("\n");
    if (start)
        return (1);
    return (revert_board(board, tetriminos, i, j, id)); // return (0);
}

int check_solve(t_board *board, t_term *tetriminos, int size, int id, int count)
{
   /* if (!tetrimino)
        return (0); */
    tetriminos[id].x = 0;
    tetriminos[id].y = 0;
    //printf("height = %d\n", tetriminos[id].height);
   // printf("width = %d\n", tetriminos[id].width);
   // printf("size = %d\n", size);
    while (tetriminos[id].y + tetriminos[id].height <= size && id < count)
    {
        tetriminos[id].x = 0;
        while (tetriminos[id].x + tetriminos[id].width <= size && id < count)
        {
            if (put_on_board(board, tetriminos, id))
            {
                if (id == count - 1)
                    return (1);
                id++;
                if (check_solve(board, tetriminos, size, id, count))
                    return (1);
                else
                    revert_board(board, tetriminos, tetriminos[id].width - 1, tetriminos[id].height - 1, id);
            }
            tetriminos[id].x++;
        }
       tetriminos[id].y++;
    }
    return (0);
}

void    solve_game(t_term	*tetriminos, int id)
{
    t_board board;
    int     size;
    int     count;

    count = id + 1;
    size = id * 4 / 2 + 1;
    init_board(&board);
    print_board(&board);
    printf("\n");
    printf("size = %d\n", size);
    while (!check_solve(&board, tetriminos, size, id, count) && size <= 12)
    {
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
