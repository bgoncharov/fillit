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

void	create_tetriminos(char *buf, int i)
{
	t_term	tetriminos[10];
	char	c = 'A';
	int		x;
	int		y;
	
	printf("buffer: \n%s", buf);
	printf("tetriminos:\n");
	x = -1;
	c = c + i;
	while (x < 4 && *buf)
	{
		x++;
		y = 0;
		while (y < 5 && *buf)
		{
			
			if (*buf == '#')
				tetriminos[i].line[x][y] = c;
			else
				tetriminos[i].line[x][y] = *buf;
			//printf("%c", tetriminos[i].line[x][y]);
			buf++;
			y++;
		}
		tetriminos[i].line[x][y] = '\0';
	}
	x = 0;
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
	printf("\n");
}

int		read_file(char *file)
{
	int	i;
	int fd;
	int ret;
	int lastret;
	char buf[255];

	i = 0;
	ret = 0;
	lastret = 0;
	if ((fd = open(file, O_RDONLY)) < 0)
		printf("open error\n");
	while ((ret = read(fd, buf, 21)) > 0)
	{
		lastret = ret;
		buf[ret] = '\0';
		if (ret >= 20 && check_block(buf))
		{
			create_tetriminos(buf, i);
			i++;
		}
		else
			printf("checking failed\n");
	}
	if (ret <= 0 && (lastret == 21 || !lastret))
		printf("errore\n");
	return (1);
}