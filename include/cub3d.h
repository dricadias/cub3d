/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 15:02:48 by adias-do          #+#    #+#             */
/*   Updated: 2026/01/11 18:28:18 by adias-do         ###   ########.fr       */
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


t_game	*init_game(void);


#endif