#ifndef FILLIT_H
# define FILLIT_H

# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

int				read_file(char *file);

typedef struct	s_term
{
	char line[4][4];
}				t_term;

#endif
