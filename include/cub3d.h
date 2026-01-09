#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x; // fov
	double	plane_y;
}	t_player;

typedef struct	s_map
{
	int			width;
	int			height;
	char		**flood;
	char		**matrix;
	t_player	player_data;
}	t_map;

/* typedef struct	s_game
{
	void	*mlx;
	void	*mlx_win;
	t_map	*map;
}	t_game;
 */

#endif