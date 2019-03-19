#include "fillit.h"
#include <stdio.h>

int     min_size(int count)
{
    int size;

	size = 2;
	while (size * size < count)
		size++;
	return (size);
}

void    init_board(t_board *board, int size)
{
    int     i;
    int     j;

    j = 0;
    while (j < size)
    {
        i = -1;
        while (i < size)
        {
            i++;
            board->s[j][i] = '.';
        }
        board->s[j][i] = '\n';
        board->s[j][i + 1] = '\0';
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
        while (k <= size)
        {
            printf("%c", board->s[j][k]);
            k++;
        }
        j++;
    }
}

/*int revert_board(t_board *board, t_term *tet, int w, int h, int id)
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
}*/

/*int put_on_board(t_board *board, t_term *tet, int id)
{
    int i;
    int j;
    int flag;
    
    j = 0;
    flag = 1;
    if (board->s[tet[id].y][tet[id].x] != '.' && tet[id].line[0][0] != '.')
        return (0);
    while (flag && j < tet[id].height)
    {
        i = 0;
        while (flag && i < tet[id].width)
        {
            if (board->s[tet[id].y + j][tet[id].x + i] != '.' && tet[id].line[j][i] != '.')
                flag = 0;
            else if (board->s[tet[id].y + j][tet[id].x + i] == '.')
                board->s[tet[id].y + j][tet[id].x + i] = tet[id].line[j][i];
            if (flag) 
                i++;
        }
        if (flag)
            j++;
    }
    if (flag)
        return (1);
    return (revert_board(board, tet, i, j, id));
}*/

void	set_piece(t_board *board, t_term *tet, char c)
{
	int i;
	int j;

	i = 0;
	while (i < tet->next->width)
	{
		j = 0;
		while (j < tet->next->height)
		{
			if (tet->next->line[j][i] != '.')
				board->s[tet->next->y + j][tet->next->x + i] = c;
			j++;
		}
		i++;
	}
}

int		place(t_board *board, t_term *tet)
{
	int i;
	int j;

	i = 0;
	while (i < tet->next->width)
	{
		j = 0;
		while (j < tet->next->height)
		{
			if (tet->next->line[j][i] != '.' && board->s[tet->next->y + j][tet->next->x + i] != '.')
				return (0);
			j++;
		}
		i++;
	}
	set_piece(board, tet, tet->next->letter);
	return (1);
}


int check_solve(t_board *board, t_term *tet, int size, int count)
{
   /* if (!tetrimino)
        return (0); */
    tet->next->y = 0;
    while (tet->next->y < size) //- tet->next->height + 1)//(tet->next->y + tet->next->height <= size)//
    {
        tet->next->x = 0;
        while (tet->next->x < size)// - tet->next->width + 1)//(tet->next->x + tet->next->width <= size)//
        {
            if (place(board, tet))//(put_on_board(board, tet))
            {
                if (check_solve(board, tet, size, count))
                    return (1);
                else
                    set_piece(board, tet, '.');//revert_board(board, tet, tet[id].width - 1, tet[id].height - 1, id);
            }
            tet->next->x++;
        }
       tet->next->y++;
    }
    return (0);
}

void    solve_game(t_term	*tet)
{
    t_board board;
    int     size;
    int     count;

    count = board.nbr;
    size = min_size(count * 4) + 1;
    init_board(&board, size);
    printf("size = %d\n", size);
   // print_board(&board, size);
    //printf("\n");
    while (!check_solve(&board, tet, size, count) && size <= 12)
    {
        size++;
        init_board(&board, size);    
    }
    printf("size = %d\n", size);
    print_board(&board, size);
    printf("\n");
}
