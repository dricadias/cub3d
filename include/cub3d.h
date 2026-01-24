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

" i feel like this should exist, dont now yet how to defin
typedef struct dir_vector
{
	its t_pos +('+' ou '-')
}  ;
  "
typedef struct	s_map
{
	int		width;
	int		height;
	char	**flood;
	char	**matrix;
	t_pos	player_pos;
}	t_map;


"typedef struct player
{
	t_pos *init_pos; 
	dir_vector *looking
	#camera width definitions... raycasting FOV (vai ser sempre o mesmo, podemos usar rato aumentar/diminuir (isto é capaz de ser uma pain in the ass por causa de minilibx rendering images))

}"

#endif