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

void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->matrix)
	{
		i = 0;
		while (map->matrix[i])
		{
			free(map->matrix[i]);
			i++;
		}
		free(map->matrix);
		map->matrix = NULL;
	}
}

void	free_config(t_map *map)
{
	if (!map)
		return ;
	if (map->no_path)
	{
		free(map->no_path);
		map->no_path = NULL;
	}
	if (map->so_path)
	{
		free(map->so_path);
		map->so_path = NULL;
	}
	if (map->we_path)
	{
		free(map->we_path);
		map->we_path = NULL;
	}
	if (map->ea_path)
	{
		free(map->ea_path);
		map->ea_path = NULL;
	}
}

void	free_texture(void *mlx, t_texture *tex)
{
	if (!tex || !mlx)
		return ;
	if (tex->img)
	{
		mlx_destroy_image(mlx, tex->img);
		tex->img = NULL;
	}
}

void	cleanup_game(t_game *game, char **file, int free_matrix_flag)
{
	if (!game)
		return ;
	if (game->mlx)
	{
		free_texture(game->mlx, &game->north);
		free_texture(game->mlx, &game->south);
		free_texture(game->mlx, &game->east);
		free_texture(game->mlx, &game->west);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game->mlx && game->img.img)
	{
		mlx_destroy_image(game->mlx, game->img.img);
	}
	if (game->mlx && game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
	}
	free_config(&game->map);
	free_map(&game->map);
	if (free_matrix_flag && file)
		free_matrix(file);
}
