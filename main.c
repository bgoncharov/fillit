#include "fillit.h"

int				main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("error in main\n");
		return (0);
	}
	if (read_file(argv[1]))
		printf("reading is ok\n");
	else
		printf("reading failed\n");

	return (0);
}