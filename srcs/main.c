/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:09:25 by adias-do          #+#    #+#             */
/*   Updated: 2026/05/09 14:20:53 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

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

static int	start_window(t_game *game, char **file)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		printf("Error\nMLX init failed\n");
		return (cleanup_game(game, file, 1), 1);
	}
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game->win)
	{
		printf("Error\nWindow creation failed\n");
		return (cleanup_game(game, file, 1), 1);
	}
	game->img.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img.img)
		return (cleanup_game(game, file, 1), 1);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
	load_texture(game->mlx, &game->north, game->map.no_path);
	load_texture(game->mlx, &game->south, game->map.so_path);
	load_texture(game->mlx, &game->east, game->map.we_path);
	load_texture(game->mlx, &game->west, game->map.ea_path);
	if (!game->north.img || !game->south.img || !game->east.img
		|| !game->west.img)
		return (cleanup_game(game, file, 1), 1);
	return (0);
}

static int	validate_and_build(t_game *game, char **file)
{
	int	start;

	parse_config(&game->map, file);
	if (!valid_config(&game->map))
		return (cleanup_game(game, file, 1), 1);
	start = map_index(file);
	if (start == -1)
	{
		printf("Error\nMap not found in file\n");
		return (cleanup_game(game, file, 1), 1);
	}
	built_map(game, file, start);
	if (!game->map.matrix)
	{
		printf("Error\nFailed to build map\n");
		return (cleanup_game(game, file, 1), 1);
	}
	if (!validate_map(&game->map))
		return (cleanup_game(game, file, 1), 1);
	init_player(game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;
	char	**file;

	ft_memset(&game, 0, sizeof(t_game));
	if (argc != 2)
		return (printf("Error\nUsage: ./cub3D map.cub\n"), 1);
	file = read_file(argv[1]);
	if (!file)
		return (1);
	if (validate_and_build(&game, file))
		return (1);
	if (start_window(&game, file))
		return (1);
	render(&game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
	cleanup_game(&game, file, 1);
	return (0);
}
