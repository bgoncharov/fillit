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

void		get_param(t_term	*tet, char *buf, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	tet[i].width = 0;
	tet[i].height = 0;
	while (j < 4)
	{
		if (buf[j] == '#' || buf[j + 5] == '#' || buf[j + 10] == '#' ||\
				buf[j + 15] == '#')
			tet[i].width++;
		j++;
	}
	while (k < 19)
	{
		if (buf[k] == '#' || buf[k + 1] == '#' || buf[k + 2] == '#' || buf[k + 3] == '#')
					tet[i].height++;
		k = k + 5;
	}
}

void	move_tet(t_term	*tet, int  id)
{
	int x;
	int y;
	int	f1;
	int f2;
	
	tet[id].x = 0;
	x = 0;
	y = 0;
	f1 = 0;
	f2 = 0;
	while (tet[id].x  < 4)
	{
		tet[id].y = 0;
		while (tet[id].y < 4)
		{
			if (tet[id].line[tet[id].x][tet[id].y] != '.')
			{
				if (tet[id].x >= x && f1 == 0)
				{
					x = tet[id].x;
					f1++;
				}
				if (tet[id].y >= y && f2 == 0)
				{
					y = tet[id].y;
					f2++;
				}
				if (f2 != 0 && tet[id].y < y)
					y = tet[id].y;
			}
			tet[id].y++;
		}
		tet[id].x++;
	}
	tet[id].x = 0;
	while (tet[id].x < 4 && x > 0)
	{
		tet[id].y = 0;
		while (tet[id].y < 4)
		{
			if (tet[id].line[tet[id].x][tet[id].y] != '.')
			{
				tet[id].line[tet[id].x - x][tet[id].y] = tet[id].line[tet[id].x][tet[id].y];
				tet[id].line[tet[id].x][tet[id].y] = '.';
			}
			tet[id].y++;
		}
		tet[id].x++;
	}
	tet[id].x = 0;
	while (tet[id].x < 4 && y > 0)
	{
		tet[id].y = 0;
		while (tet[id].y < 4)
		{
			if (tet[id].line[tet[id].x][tet[id].y] != '.')
			{
				tet[id].line[tet[id].x][tet[id].y - y] = tet[id].line[tet[id].x][tet[id].y];
				tet[id].line[tet[id].x][tet[id].y] = '.';
			}
			tet[id].y++;
		}
		tet[id].x++;
	}
}

void	create_tet(t_term	*tet, char *buf, int i)
{
	char	c = 'A';
	int		x;
	int		y;
	int		j;
	
	x = 0;
	j = 0;
	c = c + i;
	tet[i].letter = c;//?
	while (x < 4 && buf[j] != '\0')
	{
		y = 0;
		while (y < 5 && buf[j] != '\0')
		{
			if (buf[j] == '#')
				tet[i].line[x][y] = c;
			else
				tet[i].line[x][y] = buf[j];
			j++;
			y++;
		}
		tet[i].line[x][y] = '\0';
		x++;
	}
}

int		read_file(char *file, int fd)
{
	int	i;
	int ret;
	int lastret;
	char buf[255];
	static t_term	tet[26];

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
			create_tet(tet, buf, i);
			get_param(tet, buf, i);
			move_tet(tet, i);
		}
		else
		{
			ft_putstr("Error\n");
			return (0);
		}
	}
	/*i--;
	while (i >= 0)
	{
		x = 0;
		while (x < 4)
		{
			y = 0;
			while (y < 5)
			{
				printf("%c", tet[i].line[x][y]);
				y++;
			}
			x++;
		}
		i--;
		printf("\n");
	} */
	solve_game(tet, i);
	if (ret <= 0 && (lastret == 21 || !lastret))
		ft_putstr("Error\n");
	return (1);
}