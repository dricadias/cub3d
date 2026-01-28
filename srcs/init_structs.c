/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:47:30 by adias-do          #+#    #+#             */
/*   Updated: 2026/01/23 18:48:05 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_player	init_player(void)
{
	t_player	player;
	
	player.dir_x = 1;		// temporary
	player.dir_y = 0;		// temporary
	player.pos_x = 2.5;		// temporary
	player.pos_y = 3.5;		// temporary
	player.plane_x = 0;		// temporary
	player.plane_y = 0.66;	// temporary
	return (player);
}

t_map	*init_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->matrix = malloc(sizeof(char *) * 5 + 1); // temporary
	map->matrix[0] = "1111111";	// temporary
	map->matrix[1] = "1010001";	// temporary
	map->matrix[2] = "100P001";	// temporary
	map->matrix[3] = "1000001";	// temporary
	map->matrix[4] = "1111111";	// temporary
	map->width = 7;				// temporary
	map->height = 5;			// temporary
	map->player_data = init_player();

	return (map);
} 

t_game	*init_game(void) 
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->mlx = NULL;
	game->win = NULL;
	game->wall = NULL;
	game->floor = NULL;
	game->player = NULL;
	game->map = init_map();
	if (!game->map)
	{
		free(game);
		return (NULL);
	}
	return (game);
}