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
	int	i;
	int	j;

	i = 0;
	j = 0;
	tet->width = 0;
	tet->height = 0;
	while (i < 4)
	{
		if (buf[i] == '#' || buf[i + 5] == '#' || buf[i + 10] == '#' ||\
				buf[i + 15] == '#')
			tet->width++;
		i++;
	}
	while (j < 19)
	{
		if (buf[j] == '#' || buf[j + 1] == '#' ||\
		buf[j + 2] == '#' || buf[j + 3] == '#')
			tet->height++;
		j = j + 5;
	}
}

void	move_up(t_term *tet, int x, int y)
{
	tet->y = 0;
	while (tet->y < 4 && y > 0)
	{
		tet->x = 0;
		while (tet->x < 4)
		{
			if (tet->line[tet->y][tet->x] != '.')
			{
				tet->line[tet->y - y][tet->x] = tet->line[tet->y][tet->x];
				tet->line[tet->y][tet->x] = '.';
			}
			tet->x++;
		}
		tet->y++;
	}
	move_left(tet, x);
}

void	move_left(t_term *tet, int x)
{
	tet->y = 0;
	while (tet->y < 4 && x > 0)
	{
		tet->x = 0;
		while (tet->x < 4)
		{
			if (tet->line[tet->y][tet->x] != '.')
			{
				tet->line[tet->y][tet->x - x] = tet->line[tet->y][tet->x];
				tet->line[tet->y][tet->x] = '.';
			}
			tet->x++;
		}
		tet->y++;
	}
}

void	find_coord(t_term *tet, int x, int y, int f1)
{
	int f2;

	f2 = 0;
	tet->y = 0;
	while (tet->y < 4)
	{
		tet->x = 0;
		while (tet->x < 4)
		{
			if (tet->line[tet->y][tet->x] != '.')
			{
				y = (tet->y >= y && f1 == 0) ? tet->y : y;
				if (tet->y >= y && f1 == 0)
					f1++;
				x = (tet->x >= x && f2 == 0) ? tet->x : x;
				if (tet->x >= x && f2 == 0)
					f2++;
				if (f2 != 0 && tet->x < x)
					x = tet->x;
			}
			tet->x++;
		}
		tet->y++;
	}
	move_up(tet, x, y);
}

t_term	*create_tet(char *buf)
{
	t_term		*tet;
	static char	c = 'A';

	tet = ft_memalloc(sizeof(t_term));
	tet->y = 0;
	tet->letter = c;
	tet->next = NULL;
	while (tet->y < 4 && *buf)
	{
		tet->x = 0;
		while (tet->x < 5 && *buf)
		{
			if (*buf == '#')
				tet->line[tet->y][tet->x] = c;
			else
				tet->line[tet->y][tet->x] = *buf;
			buf++;
			tet->x++;
		}
		tet->line[tet->y][tet->x] = '\0';
		tet->y++;
	}
	c++;
	return (tet);
}
