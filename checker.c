#include "fillit.h"

static int		is_valid(int c, int i)
{
	if (c == '.' || c == '#'
		|| ((c == '\n') && ((i % 5 == 4) || (i == 20))))
		return (1);
	return (0);
}

static int		check_tet(char *buf, int i)
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

static int		check_block(char *buf)
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
		{
			//printf("check is OK\n");
			return (1);
		}
	}
	else
		printf("check error\n");
	return (0);
}

void		get_param(t_term	*tet, char *buf)
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
		if (buf[k] == '#' || buf[k + 1] == '#' || buf[k + 2] == '#' || buf[k + 3] == '#')
					tet->height++;
		k = k + 5;
	}
}

void	move_tet(t_term	*tet)
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
	while (tet->x  < 4)
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
	t_term	*tet;
	static char	c = 'A';
	int		x;
	int		y;
	int		j;
	
	x = 0;
	j = 0;
	tet = ft_memalloc(sizeof(t_term));
	tet->x = 0;
	tet->y = 0;
	tet->letter = c++;
	tet->next = NULL;
	while (x < 4 && buf[j] != '\0')
	{
		y = 0;
		while (y < 5 && buf[j] != '\0')
		{
			if (buf[j] == '#')
				tet->line[x][y] = c;
			else
				tet->line[x][y] = buf[j];
			j++;
			y++;
		}
		tet->line[x][y] = '\0';
		x++;
	}
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

int		read_file(char *file, int fd)
{
	int	i;
	int ret;
	int lastret;
	char buf[255];
	//char temp[4][5];
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
	solve_game(tet);
	if (ret <= 0 && (lastret == 21 || !lastret))
		ft_putstr("Error\n");
	return (1);
}