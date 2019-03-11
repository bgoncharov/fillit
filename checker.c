#include "fillit.h"

static int		is_valid(int c, int i)
{
	if (c == TEMPTY || c == TPART
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
	if (buf[i] == TPART)
	{
		if (i > 0 && buf[i - 1] == TPART)
			count++;
		if (i < 19 && buf[i + 1] == TPART)
			count++;
		if (i >= 5 && buf[i - 5] == TPART)
			count++;
		if (i < 14 && buf[i + 5] == TPART)
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
		if (buf[i] == TPART)
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
			printf("check is OK\n");
			return (1);
		}
	}
	else
		printf("check error\n");
	return (0);
}

int		read_file(char *file)
{
	int fd;
	int ret;
	int lastret;
	char buf[255];

	ret = 0;
	lastret = 0;
	if ((fd = open(file, O_RDONLY)) < 0)
		printf("open error\n");
	while ((ret = read(fd, buf, 21)) > 0)
	{
		lastret = ret;
		buf[ret] = '\0';
		if (ret >= 20 && check_block(buf))
			printf("ckeck [OK]\n");
		else
			printf("checking failed\n");
	}
	if (ret <= 0 && (lastret == 21 || !lastret))
		printf("errore\n");
	return (1);
}