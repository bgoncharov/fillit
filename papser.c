#include "fillit.h"

int		read_file(char *file)
{
	int fd;
	int ret;
	int lastret;
	char buf[255];

	ret = 0;
	lastret = 0;
	if ((fd = open(file, O_RDONLY)) < 0)
		printf("errore");
	while ((ret = read(fd, buf, 21)) > 0)
	{
		lastret = ret;
		buf[ret] = '\0';
		if (ret >= 20 && check(buf))
			sohranit(kuda, buf);
		else
			printf("errore");
	}
	if (ret <= 0 && (lastret == 21 || lastret))
		printf("errore");
	return (1);
}