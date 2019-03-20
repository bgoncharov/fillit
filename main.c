/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogoncha <bogoncha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 10:39:47 by kdenisov          #+#    #+#             */
/*   Updated: 2019/03/20 15:39:09 by bogoncha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		ft_error(void)
{
	ft_putstr("error\n");
	exit(0);
}

void	pushback(t_board *board, t_term *tet)
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

void	get_tet(t_board *board, char *buf)
{
	int		x;
	int		y;
	int		f1;
	t_term	*tet;

	x = 0;
	y = 0;
	f1 = 0;
	tet = create_tet(buf);
	get_param(tet, buf);
	tet->y = 0;
	find_coord(tet, x, y, f1);
	pushback(board, tet);
}

int		read_file(char *file, int fd, t_board *board)
{
	int		i;
	int		ret;
	int		lastret;
	char	buf[22];

	i = -1;
	ret = 0;
	lastret = 0;
	if ((fd = open(file, O_RDONLY)) < 0)
		ft_error();
	while ((ret = read(fd, buf, 21)) > 0)
	{
		lastret = ret;
		buf[ret] = '\0';
		if (ret >= 20 && check_block(buf) && i < 26)
		{
			i++;
			get_tet(board, buf);
		}
		else
			ft_error();
	}
	if (ret <= 0 && (lastret == 21 || !lastret))
		ft_error();
	return (1);
}

int		main(int argc, char **argv)
{
	if (argc == 2)
	{
		int		fd;
		t_board board;

		board.tetrs = NULL;
		board.nbr = 0;
		fd = 0;
		if (read_file(argv[1], fd, &board))
			solve_game(&board);
		else
			ft_putstr("Error\n");
	}
	else
		ft_putstr("usage: ./fillit [file_name]\n");
	return (0);
}
