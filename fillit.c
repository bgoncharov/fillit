/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogoncha <bogoncha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 10:49:03 by bogoncha          #+#    #+#             */
/*   Updated: 2019/03/20 11:02:05 by bogoncha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

void		set_piece(t_board *board, t_term *tet, char c)
{
	int		i;
	int		j;

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

int			place(t_board *board, t_term *tet)
{
	int		i;
	int		j;

	i = 0;
	while (i < tet->width)
	{
		j = 0;
		while (j < tet->height)
		{
			if (tet->line[j][i] != '.' &&
				board->s[tet->y + j][tet->x + i] != '.')
				return (0);
			j++;
		}
		i++;
	}
	set_piece(board, tet, tet->letter);
	return (1);
}

int			check_solve(t_board *board, t_term *tet, int size)
{
	tet->y = 0;
	while (tet->y < size)
	{
		tet->x = 0;
		while (tet->x < size)
		{
			if (place(board, tet))
			{
				if (!tet->next)
					return (1);
				if (tet->next && check_solve(board, tet->next, size))
					return (1);
				else
					set_piece(board, tet, '.');
			}
			tet->x++;
		}
		tet->y++;
	}
	return (0);
}

void		solve_game(t_board *board)
{
	int		size;

	size = min_size(board->nbr * 4);
	init_board(board, size);
	printf("size = %d\n", size);
	while (!check_solve(board, board->tetrs, size) && size <= 12)
	{
		size++;
		init_board(board, size);
	}
	printf("size = %d\n", size);
	print_board(board, size);
	ft_putstr("\n");
}
