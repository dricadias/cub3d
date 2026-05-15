/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anferrei <anferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 13:22:25 by anferrei          #+#    #+#             */
/*   Updated: 2026/04/09 13:22:25 by anferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_game(t_game *game)
{
	if (!game)
		return ;
	game->mlx = NULL;
	game->win = NULL;
	game->img.img = NULL;
	game->img.addr = NULL;
	game->map.matrix = NULL;
	game->map.no_path = NULL;
	game->map.so_path = NULL;
	game->map.we_path = NULL;
	game->map.ea_path = NULL;
	game->north.img = NULL;
	game->south.img = NULL;
	game->east.img = NULL;
	game->west.img = NULL;
}

void	free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

// Esta função limpa os paths e as texturas MLX
void	free_resources(t_game *game)
{
	if (game->map.no_path)
		free(game->map.no_path);
	if (game->map.so_path)
		free(game->map.so_path);
	if (game->map.we_path)
		free(game->map.we_path);
	if (game->map.ea_path)
		free(game->map.ea_path);
	if (game->mlx)
	{
		if (game->north.img)
			mlx_destroy_image(game->mlx, game->north.img);
		if (game->south.img)
			mlx_destroy_image(game->mlx, game->south.img);
		if (game->east.img)
			mlx_destroy_image(game->mlx, game->east.img);
		if (game->west.img)
			mlx_destroy_image(game->mlx, game->west.img);
		if (game->img.img)
			mlx_destroy_image(game->mlx, game->img.img);
	}
}

void	cleanup_game(t_game *game, char **file, int free_file_flag)
{
	if (!game)
		return ;
	free_resources(game);
	free_matrix(game->map.matrix);
	if (free_file_flag && file)
		free_matrix(file);
	if (game->mlx)
	{
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}
