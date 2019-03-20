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
		ft_putstr("Error\n");
	/* system("leaks a.out"); */
	return (0);
}
