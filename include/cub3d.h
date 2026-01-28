/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 15:02:48 by adias-do          #+#    #+#             */
/*   Updated: 2026/01/23 18:49:24 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define TILE 32
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

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
	//char		**flood;
	char		**matrix;
	t_player	player_data;
}	t_map;

typedef struct	s_game
{
	void	*mlx;
	void	*win;
	void	*floor;
	void	*player;
	void	*wall;
	t_map	*map;
}	t_game;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;


// init structs
t_map		*init_map(void);
t_game		*init_game(void);
t_player	init_player(void);

// draw functions
void	pixel_put(t_data *data, int x, int y, int color);
void	draw_tile(t_data *img, int tile_x, int tile_y, int color);
void	draw_map2d(t_map *map, t_data *img);
void	draw_player(t_player *player, t_data *img);


#endif