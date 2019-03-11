#include "fillit.h"

int				main(int argc, char **argv)
{
	t_term tetriminos[10];
/*	char	str[] = "123";
	int x;
	int y; */

	tetriminos[0].line[0][0] = 'v';
	tetriminos[0].line[0][1] = 'p';

	
	if (argc != 2)
	{
		printf("error in main\n");
		printf("%s\n", tetriminos[0].line[0]);
		return (0);
	}
	if (read_file(argv[1]))
		printf("reading is finished\n");
	else
		printf("reading failed\n");

	return (0);
}
