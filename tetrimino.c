/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetrimino.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogoncha <bogoncha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:09:02 by kdenisov          #+#    #+#             */
/*   Updated: 2019/03/20 00:00:05 by bogoncha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	get_param(t_term *tet, char *buf)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	tet->width = 0;
	tet->height = 0;
	while (j < 4)
	{
		if (buf[j] == '#' || buf[j + 5] == '#' || buf[j + 10] == '#' ||\
				buf[j + 15] == '#')
			tet->width++;
		j++;
	}
	while (k < 19)
	{
		if (buf[k] == '#' || buf[k + 1] == '#' ||\
		buf[k + 2] == '#' || buf[k + 3] == '#')
			tet->height++;
		k = k + 5;
	}
}

void	move_tet(t_term *tet)
{
	int x;
	int y;
	int	f1;
	int f2;

	tet->x = 0;
	x = 0;
	y = 0;
	f1 = 0;
	f2 = 0;
	while (tet->x < 4)
	{
		tet->y = 0;
		while (tet->y < 4)
		{
			if (tet->line[tet->x][tet->y] != '.')
			{
				if (tet->x >= x && f1 == 0)
				{
					x = tet->x;
					f1++;
				}
				if (tet->y >= y && f2 == 0)
				{
					y = tet->y;
					f2++;
				}
				if (f2 != 0 && tet->y < y)
					y = tet->y;
			}
			tet->y++;
		}
		tet->x++;
	}
	tet->x = 0;
	while (tet->x < 4 && x > 0)
	{
		tet->y = 0;
		while (tet->y < 4)
		{
			if (tet->line[tet->x][tet->y] != '.')
			{
				tet->line[tet->x - x][tet->y] = tet->line[tet->x][tet->y];
				tet->line[tet->x][tet->y] = '.';
			}
			tet->y++;
		}
		tet->x++;
	}
	tet->x = 0;
	while (tet->x < 4 && y > 0)
	{
		tet->y = 0;
		while (tet->y < 4)
		{
			if (tet->line[tet->x][tet->y] != '.')
			{
				tet->line[tet->x][tet->y - y] = tet->line[tet->x][tet->y];
				tet->line[tet->x][tet->y] = '.';
			}
			tet->y++;
		}
		tet->x++;
	}
}

t_term	*create_tet(char *buf)
{
	t_term		*tet;
	static char	c = 'A';

	tet = ft_memalloc(sizeof(t_term));
	tet->x = 0;
	tet->letter = c;
	tet->next = NULL;
	while (tet->x < 4 && *buf)
	{
		tet->y = 0;
		while (tet->y < 5 && *buf)
		{
			if (*buf == '#')
				tet->line[tet->x][tet->y] = c;
			else
				tet->line[tet->x][tet->y] = *buf;
			buf++;
			tet->y++;
		}
		tet->line[tet->x][tet->y] = '\0';
		tet->x++;
	}
	c++;
	return (tet);
}

void			pushback(t_board *board, t_term *tet)
{
	t_term		*new;

	new = board->tetrs;
	if (!new)
	{
		board->tetrs = tet;
		board->nbr++;
	}
	else
	{
		while (new->next)
			new = new->next;
		new->next = tet;
		board->nbr++;
	}
}