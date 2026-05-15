/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anferrei <anferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:00:21 by anferrei          #+#    #+#             */
/*   Updated: 2026/04/09 14:00:21 by anferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	set_player_dir(t_game *game, char dir)
{
	if (dir == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
	}
	else if (dir == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0;
	}
}

static void	set_player_dir_extra(t_game *game, char dir)
{
	if (dir == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
}

void	init_player(t_game *game)
{
	game->player.pos_x = game->map.player_pos.x;
	game->player.pos_y = game->map.player_pos.y;
	set_player_dir(game, game->map.player_dir);
	set_player_dir_extra(game, game->map.player_dir);
}

int	validate_map(t_map *map)
{
	if (!map)
		return (printf("Error\nNull map pointer\n"), 0);
	if (!map->matrix)
		return (printf("Error\nMap matrix not allocated\n"), 0);
	if (!check_borders(map))
		return (0);
	if (!find_player(map))
		return (0);
	if (!check_leaks(map))
		return (0);
	return (1);
}
