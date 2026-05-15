/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:09:25 by adias-do          #+#    #+#             */
/*   Updated: 2026/05/15 01:38:12 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	setup_graphics(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (printf("Error\nInitialize MLX\n"), 0);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game->win)
		return (printf("Error\nFailed to create window\n"), 0);
	game->img.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img.img)
		return (0);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
	load_texture(game->mlx, &game->north, game->map.no_path);
	load_texture(game->mlx, &game->south, game->map.so_path);
	load_texture(game->mlx, &game->east, game->map.ea_path);
	load_texture(game->mlx, &game->west, game->map.we_path);
	if (!game->north.img || !game->south.img || !game->east.img
		|| !game->west.img)
		return (0);
	return (1);
}

static int	parse_and_build(t_game *game, char **file)
{
	int	start;

	parse_config(&game->map, file);
	if (!valid_config(&game->map))
		return (0);
	start = map_index(file);
	if (start == -1)
		return (printf("Error\nMap not found in file\n"), 0);
	built_map(game, file, start);
	if (!game->map.matrix)
		return (printf("Error\nFailed to build map\n"), 0);
	if (!validate_map(&game->map))
		return (0);
	init_player(game);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;
	char	**file;

	if (argc != 2)
		return (printf("Error\nUsage: ./cub3D map.cub\n"), 1);
	init_game(&game);
	file = read_file(argv[1]);
	if (!file)
		return (1);
	if (!parse_and_build(&game, file))
		return (cleanup_game(&game, file, 1), 1);
	if (!setup_graphics(&game))
		return (cleanup_game(&game, file, 1), 1);
	render(&game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
	cleanup_game(&game, file, 1);
	return (0);
}
