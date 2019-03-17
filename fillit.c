#include "fillit.h"
#include <stdio.h>

int     min_size(int count)
{
    int size;

	size = 1;
	while (size * size < count)
		size++;
	return (size);
}

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

void    print_board(t_board *board, int size)
{
    int     j;
    int     k;

    j = 0;
    while (j < size)
    {
        k = 0;
        while (k < size)
        {
            printf("%c", board->s[j][k]);
            k++;
        }
        printf("\n");
        j++;
    }
}

int revert_board(t_board *board, t_term *tet, int w, int h, int id)
{
    int i;
    int j;

    j = 0;
    if (h > 0)
        w = tet[id].width - 1;
    while (j <= w)
    {
        i = 0;
        while (i <= w)
        {
            if (board->s[tet[id].y + j][tet[id].x + i] == tet[id].line[j][i])
                board->s[tet[id].y + j][tet[id].x + i] = '.';
            i++;
        }
        j++;
    }
    return (0);
}

int put_on_board(t_board *board, t_term *tet, int id)
{
    int i;
    int j;
    int start;

    j = 0;
    start = 1;
    if (board->s[tet[id].y][tet[id].x] != '.' && tet[id].line[0][0] != '.')
        return (0);
    while (start && j <= tet[id].height)
    {
        i = 0;
        while (start && i <= tet[id].width)
        {
            if (board->s[tet[id].y + j][tet[id].x + i] != '.' && tet[id].line[j][i] != '.')
                start = 0;
            else if (board->s[tet[id].y + j][tet[id].x + i] == '.')
            {
                board->s[tet[id].y + j][tet[id].x + i] = tet[id].line[j][i];
            }
            if (start) 
                i++;
        }
        if (start) 
            j++;
    }
    if (start)
        return (1);
    return (revert_board(board, tet, i, j, id));
}

int check_solve(t_board *board, t_term *tet, int size, int id, int count)
{
   /* if (!tetrimino)
        return (0); */
    tet[id].x = 0;
    tet[id].y = 0;
    while (tet[id].y + tet[id].height <= size && id < count)
    {
        tet[id].x = 0;
        while (tet[id].x + tet[id].width <= size && id < count)
        {
            if (put_on_board(board, tet, id))
            {
                if (id == count - 1)
                    return (1);
                id++;
                if (check_solve(board, tet, size, id, count))
                    return (1);
                else
                    revert_board(board, tet, tet[id].width - 1, tet[id].height - 1, id);
            }
            tet[id].x++;
        }
       tet[id].y++;
    }
    return (0);
}

void    solve_game(t_term	*tet, int id)
{
    t_board board;
    int     size;
    int     count;

    count = id + 1;
    size = min_size(count) * 2 - 1;
    init_board(&board);
    printf("size = %d\n", size);
    print_board(&board, size);
    printf("\n");
    while (!check_solve(&board, tet, size, id, count) && size <= 12)
    {
        size++;
        init_board(&board);    
    }
    printf("size = %d\n", size);
    print_board(&board, size);
    printf("\n");
}
