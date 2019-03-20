#include "fillit.h"
#include <stdio.h>

int		min_size(int count)
{
	int		size;

	size = 2;
	while (size * size < count)
		size++;
	return (size);
}

void	init_board(t_board *board, int size)
{
	int		i;
	int		j;
	
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

void	print_board(t_board *board, int size)
{
	int		j;
	int		k;
	
	j = 0;
	while (j < size)
	{
		k = 0;
		while (k <= size)
		{
			ft_putchar(board->s[j][k]);
			k++;
		}
		j++;
	}
}
