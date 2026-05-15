/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anferrei <anferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 13:49:30 by anferrei          #+#    #+#             */
/*   Updated: 2026/04/09 13:49:30 by anferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	check_tile_leaks(t_map *map, int y, int x)
{
	if (y == 0 || y == map->height - 1
		|| x == 0 || x == map->width - 1)
		return (printf("Error\nMap is not enclosed (edge)\n"), 0);
	if (y > 0 && map->matrix[y - 1][x] == ' ')
		return (printf("Error\nLeak above at y=%d, x=%d\n", y, x), 0);
	if (y < map->height - 1 && map->matrix[y + 1][x] == ' ')
		return (printf("Error\nLeak below at y=%d, x=%d\n", y, x), 0);
	if (x > 0 && map->matrix[y][x - 1] == ' ')
		return (printf("Error\nLeak left at y=%d, x=%d\n", y, x), 0);
	if (x < map->width - 1 && map->matrix[y][x + 1] == ' ')
		return (printf("Error\nLeak right at y=%d, x=%d\n", y, x), 0);
	return (1);
}

int	check_leaks(t_map *map)
{
	int	x;
	int	y;

	if (!map || !map->matrix)
		return (printf("Error\nInvalid map for leak check\n"), 0);
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (map->matrix[y][x] != '0' && !is_player(map->matrix[y][x])
				&& map->matrix[y][x] != '1' && map->matrix[y][x] != ' ')
				return (printf("Error\nInvalid char in map\n"), 0);
			if (map->matrix[y][x] == '0' || is_player(map->matrix[y][x]))
			{
				if (!check_tile_leaks(map, y, x))
					return (0);
			}
		}
	}
	return (1);
}

int	find_player(t_map *map)
{
	int	x;
	int	y;
	int	count;

	if (!map || !map->matrix)
		return (printf("Error\nInvalid map for player search\n"), 0);
	count = 0;
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (is_player(map->matrix[y][x]))
			{
				map->player_pos.x = x + 0.5;
				map->player_pos.y = y + 0.5;
				map->player_dir = map->matrix[y][x];
				count++;
			}
		}
	}
	if (count != 1)
		return (printf("Error\nPlayer count is %d (must be 1)\n", count), 0);
	return (1);
}

static int	check_vertical_borders(t_map *map)
{
	int	y;

	y = 0;
	while (y < map->height)
	{
		if (map->matrix[y][0] != '1' && map->matrix[y][0] != ' ')
			return (printf("Error\nBorder fail left y=%d\n", y), 0);
		if (map->matrix[y][map->width - 1] != '1'
			&& map->matrix[y][map->width - 1] != ' ')
			return (printf("Error\nBorder fail right y=%d\n", y), 0);
		y++;
	}
	return (1);
}

int	check_borders(t_map *map)
{
	int	x;

	if (!map || !map->matrix || map->height <= 0 || map->width <= 0)
		return (printf("Error\nInvalid map dimensions\n"), 0);
	x = 0;
	while (x < map->width)
	{
		if (map->matrix[0][x] != '1' && map->matrix[0][x] != ' ')
			return (printf("Error\nBorder fail top x=%d\n", x), 0);
		if (map->matrix[map->height - 1][x] != '1'
			&& map->matrix[map->height - 1][x] != ' ')
			return (printf("Error\nBorder fail bottom x=%d\n", x), 0);
		x++;
	}
	return (check_vertical_borders(map));
}
