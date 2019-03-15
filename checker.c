#include "fillit.h"

static int		is_valid(int c, int i)
{
	if (c == '.' || c == '#'
		|| ((c == '\n') && ((i % 5 == 4) || (i == 20))))
		return (1);
	return (0);
}

static int		check_terminitos(char *buf, int i)
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
	return (count + check_terminitos(buf, ++i));
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
		res = check_terminitos(buf, start);
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

void		get_param(t_term	*tetriminos, char *buf, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	tetriminos[i].width = 0;
	tetriminos[i].height = 0;
	while (j < 4)
	{
		if (buf[j] == '#' || buf[j + 5] == '#' || buf[j + 10] == '#' ||\
				buf[j + 15] == '#')
			tetriminos[i].width++;
		j++;
	}
	while (k < 19)
	{
		if (buf[k] == '#' || buf[k + 1] == '#' || buf[k + 2] == '#' || buf[k + 3] == '#')
					tetriminos[i].height++;
		k = k + 5;
	}
}

void	move_tet(t_term	*tetriminos, int  id)
{
	int x;
	int y;
	int	f1;
	int f2;
	
	tetriminos[id].x = 0;
	x = 0;
	y = 0;
	f1 = 0;
	f2 = 0;
	while (tetriminos[id].x  < 4)
	{
		tetriminos[id].y = 0;
		while (tetriminos[id].y < 4)
		{
			if (tetriminos[id].line[tetriminos[id].x][tetriminos[id].y] != '.')
			{
				if (tetriminos[id].x >= x && f1 == 0)
				{
					x = tetriminos[id].x;
					f1++;
				}
				if (tetriminos[id].y >= y && f2 == 0)
				{
					y = tetriminos[id].y;
					f2++;
				}
				if (f2 != 0 && tetriminos[id].y < y)
					y = tetriminos[id].y;
			}
			tetriminos[id].y++;
		}
		tetriminos[id].x++;
	}
	printf("id = %d\n", id);
	printf("x = %d\n", x);
	printf("y = %d\n\n", y);
	tetriminos[id].x = 0;
	while (tetriminos[id].x < 4 && x > 0)
	{
		tetriminos[id].y = 0;
		while (tetriminos[id].y < 4)
		{
			if (tetriminos[id].line[tetriminos[id].x][tetriminos[id].y] != '.')
			{
				tetriminos[id].line[tetriminos[id].x - x][tetriminos[id].y] = tetriminos[id].line[tetriminos[id].x][tetriminos[id].y];
				tetriminos[id].line[tetriminos[id].x][tetriminos[id].y] = '.';
			}
			tetriminos[id].y++;
		}
		tetriminos[id].x++;
	}
	tetriminos[id].x = 0;
	while (tetriminos[id].x < 4 && y > 0)
	{
		tetriminos[id].y = 0;
		while (tetriminos[id].y < 4)
		{
			if (tetriminos[id].line[tetriminos[id].x][tetriminos[id].y] != '.')
			{
				tetriminos[id].line[tetriminos[id].x][tetriminos[id].y - y] = tetriminos[id].line[tetriminos[id].x][tetriminos[id].y];
				tetriminos[id].line[tetriminos[id].x][tetriminos[id].y] = '.';
			}
			tetriminos[id].y++;
		}
		tetriminos[id].x++;
	}
}

void	create_tetriminos(t_term	*tetriminos, char *buf, int i)
{
	char	c = 'A';
	int		x;
	int		y;
	int		j;
	
	x = 0;
	j = 0;
	c = c + i;
	while (x < 4 && buf[j] != '\0')
	{
		y = 0;
		while (y < 5 && buf[j] != '\0')
		{
			if (buf[j] == '#')
				tetriminos[i].line[x][y] = c;
			else
				tetriminos[i].line[x][y] = buf[j];
			j++;
			y++;
		}
		tetriminos[i].line[x][y] = '\0';
		x++;
	}
}

int		read_file(char *file, int fd)
{
	int	i;
	int ret;
	int lastret;
	char buf[255];
	static t_term	tetriminos[26];
	//int		x;
	//int		y;

	i = -1;
	ret = 0;
	lastret = 0;
	if ((fd = open(file, O_RDONLY)) < 0)
	{
		ft_putstr("Error\n");
		return (0);
	}
	while ((ret = read(fd, buf, 21)) > 0)
	{
		lastret = ret;
		buf[ret] = '\0';
		if (ret >= 20 && check_block(buf) && i < 26)
		{
			i++;
			create_tetriminos(tetriminos, buf, i);
			get_param(tetriminos, buf, i);
			move_tet(tetriminos, i);
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
		printf("width: %d\n", (int)tetriminos[i].width);
		printf("height: %d\n", (int)tetriminos[i].height);
		while (x < 4)
		{
			y = 0;
			while (y < 5)
			{
				printf("%c", tetriminos[i].line[x][y]);
				y++;
			}
			x++;
		}
		i--;
		printf("\n");
	} */
	solve_game(tetriminos, i);
	if (ret <= 0 && (lastret == 21 || !lastret))
		ft_putstr("Error\n");
	return (1);
}