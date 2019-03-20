/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdenisov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 10:39:47 by kdenisov          #+#    #+#             */
/*   Updated: 2019/03/20 10:39:53 by kdenisov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		ft_error(void)
{
	ft_putstr("Error\n");
	exit(0);
}

void	get_tet(t_board *board, char *buf)
{
	t_term	*tet;

	tet = create_tet(buf);
	get_param(tet, buf);
	find_coord(tet);
	pushback(board, tet);
}

int		read_file(char *file, int fd, t_board *board)
{
	int		i;
	int		ret;
	int		lastret;
	char	buf[255];

	i = -1;
	ret = 0;
	lastret = 0;
	if ((fd = open(file, O_RDONLY)) < 0)
		ft_error();
	while ((ret = read(fd, buf, 21)) >= 20)
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
	int		fd;
	t_board board;

	board.tetrs = NULL;
	board.nbr = 0;
	fd = 0;
	if (argc != 2)
	{
		printf("error in main\n");
		return (0);
	}
	if (read_file(argv[1], fd, &board))
		solve_game(&board);
	else
		ft_putstr("Error\n");
	return (0);
}
