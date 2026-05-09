/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 03:43:03 by adias-do          #+#    #+#             */
/*   Updated: 2026/05/09 14:13:17 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	key_press(int keysym, t_game *game)
{
	if (keysym == XK_Escape)
		close_window(game);
	if (keysym == XK_w)
		move_player(game, 1);
	if (keysym == XK_a)
		strafe_player(game, -1);
	if (keysym == XK_s)
		move_player(game, -1);
	if (keysym == XK_d)
		strafe_player(game, 1);
	if (keysym == XK_Right)
		rotate_player(game, 1);
	if (keysym == XK_Left)
		rotate_player(game, -1);
	render(game);
	return (0);
}

void	move_player(t_game *game, double move_dir)
{
	double	new_x;
	double	new_y;
	double	speed;

	speed = 0.2;
	new_x = game->player.pos_x + (game->player.dir_x * move_dir * speed);
	new_y = game->player.pos_y + (game->player.dir_y * move_dir * speed);
	if (game->map.matrix[(int)game->player.pos_y][(int)new_x] != '1')
		game->player.pos_x = new_x;
	if (game->map.matrix[(int)new_y][(int)game->player.pos_x] != '1')
		game->player.pos_y = new_y;
}

void	rotate_player(t_game *game, double rot_dir)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;
	double	angle;

	rot_speed = 0.1;
	angle = rot_speed * rot_dir;
	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(angle)
		- game->player.dir_y * sin(angle);
	game->player.dir_y = old_dir_x * sin(angle)
		+ game->player.dir_y * cos(angle);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(angle)
		- game->player.plane_y * sin(angle);
	game->player.plane_y = old_plane_x * sin(angle)
		+ game->player.plane_y * cos(angle);
}

void	strafe_player(t_game *game, double strafe_dir)
{
	double	new_x;
	double	new_y;
	double	speed;

	speed = 0.2;
	new_x = game->player.pos_x - (game->player.dir_y * strafe_dir * speed);
	new_y = game->player.pos_y + (game->player.dir_x * strafe_dir * speed);
	if (game->map.matrix[(int)game->player.pos_y][(int)new_x] != '1')
		game->player.pos_x = new_x;
	if (game->map.matrix[(int)new_y][(int)game->player.pos_x] != '1')
		game->player.pos_y = new_y;
}
