#include "fillit.h"

int		is_valid(int c, int i)
{
	if (c == '.' || c == '#'
		|| ((c == '\n') && ((i % 5 == 4) || (i == 20))))
		return (1);
	return (0);
}

int		check_tet(char *buf, int i)
{
	int count;

	if (i == 19)
		return (0);
	count = 0;
	if (buf[i] == '#')
	{
		if (i > 0 && buf[i - 1] == '#')
			count++;
		if (i < 19 && buf[i + 1] == '#')
			count++;
		if (i >= 5 && buf[i - 5] == '#')
			count++;
		if (i < 14 && buf[i + 5] == '#')
			count++;
	}
	return (count + check_tet(buf, ++i));
}

int		check_block(char *buf)
{
	int i;
	int part;
	int start;
	int res;

	i = 0;
	part = 0;
	while (buf[i] && is_valid(buf[i], i) && part <= 4)
	{
		if (buf[i] == '#')
		{
			part++;
			if (part == 1)
				start = i;
		}
		i++;
	}
	if (i >= 20 && !buf[i] && part == 4)
	{
		res = check_tet(buf, start);
		if (res == 6 || res == 8)
			return (1);
	}
	else
		ft_putstr("Error\n");
	return (0);
}

int		read_file(char *file, int fd)
{
	int		i;
	int		ret;
	int		lastret;
	char	buf[255];
	t_term	*tet;
	t_board board;

	board.tetrs = NULL;
	board.nbr = 0;
	i = -1;
	ret = 0;
	lastret = 0;
	if ((fd = open(file, O_RDONLY)) < 0)
	{
		ft_putstr("Error\n");
		return (0);
	}
	while ((ret = read(fd, buf, 21)) >= 20)
	{
		lastret = ret;
		buf[ret] = '\0';
		if (ret >= 20 && check_block(buf) && i < 26)
		{
			i++;
			tet = create_tet(buf);
			get_param(tet, buf);
			move_tet(tet);
			pushback(&board, tet);
		}
		else
		{
			ft_putstr("Error\n");
			return (0);
		}
	}
	if (ret <= 0 && (lastret == 21 || !lastret))
		ft_putstr("Error\n");
	solve_game(&board);
	return (1);
}
