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

void	set_piece(t_board *board, t_term *tet, char c)
{
	int i;
	int j;

	i = 0;
	while (i < tet->width)
	{
		j = 0;
		while (j < tet->height)
		{
			if (tet->line[j][i] != '.')
				board->s[tet->y + j][tet->x + i] = c;
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
	while (i < tet->width)
	{
		j = 0;
		while (j < tet->height)
		{
			if (tet->line[j][i] != '.' && board->s[tet->y + j][tet->x + i] != '.')
				return (0);
			j++;
		}
		i++;
	}
	set_piece(board, tet, tet->letter);
	return (1);
}


int check_solve(t_board *board, t_term *tet, int size, int count)
{
   /* if (!tetrimino)
        return (0); */
    tet->y = 0;
    while (tet->y < size) //- tet->next->height + 1)//(tet->next->y + tet->next->height <= size)//
    {
        tet->x = 0;
        while (tet->x < size)// - tet->next->width + 1)//(tet->next->x + tet->next->width <= size)//
        {
            if (place(board,  tet))//(put_on_board(board, tet))
            {
                if (!tet->next)
                    return (1);
                if (tet->next && check_solve(board, tet->next, size, count))
                    return (1);
                else
                    set_piece(board,  tet, '.');//revert_board(board, tet, tet[id].width - 1, tet[id].height - 1, id);
            }
            tet->x++;
        }
        tet->y++;
    }
    return (0);
}

void    solve_game(t_board *board)
{
    int     size;
    int     count;

    count = board->nbr;
    size = min_size(count * 4);
    init_board(board, size);
    printf("size = %d\n", size);
   // print_board(&board, size);
    //printf("\n");
    while (!check_solve(board, board->tetrs, size, count) && size <= 12)
    {
        size++;
        init_board(board, size);    
    }
    printf("size = %d\n", size);
    print_board(board, size);
    printf("\n");
}
