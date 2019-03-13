#include "fillit.h"

int				main(int argc, char **argv)
{
	int	fd;

	fd = 0;
	if (argc != 2)
	{
		printf("error in main\n");
		return (0);
	}
	if (!read_file(argv[1], fd))
	//	printf("reading is ok\n");
	//else
		ft_putstr("Error\n");

	return (0);
}