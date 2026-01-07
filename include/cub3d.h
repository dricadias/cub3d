#ifndef CUB3D
# define CUB3D

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>

typedef struct s_pos
{
	double	x;
	double	y;
}	t_pos;

typedef struct	s_map
{
	int		width;
	int		height;
	char	**flood;
	char	**matrix;
	t_pos	player_pos;
}	t_map;



#endif