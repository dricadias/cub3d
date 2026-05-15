/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anferrei <anferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 13:49:30 by anferrei          #+#    #+#             */
/*   Updated: 2026/05/15 01:50:00 by anferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	is_leak(t_map *map, int y, int x)
{
	if (y == 0 || y == map->height - 1 || x == 0 || x == map->width - 1)
		return (printf("Error\nMap not enclosed at edge\n"), 1);
	if (map->matrix[y - 1][x] == ' ' || map->matrix[y + 1][x] == ' ')
		return (printf("Error\nMap leak at y:%d x:%d\n", y, x), 1);
	if (map->matrix[y][x - 1] == ' ' || map->matrix[y][x + 1] == ' ')
		return (printf("Error\nMap leak at y:%d x:%d\n", y, x), 1);
	return (0);
}

int	check_leaks(t_map *map)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (map->matrix[y][x] == '0' || is_player(map->matrix[y][x]))
			{
				if (is_leak(map, y, x))
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
		return (printf("Error\nInvalid player count: %d\n", count), 0);
	return (1);
}

int	check_borders(t_map *map)
{
	int	i;

	i = -1;
	while (++i < map->width)
	{
		if ((map->matrix[0][i] != '1' && map->matrix[0][i] != ' ') ||
			(map->matrix[map->height - 1][i] != '1' &&
			map->matrix[map->height - 1][i] != ' '))
			return (printf("Error\nInvalid char at top/bot border\n"), 0);
	}
	i = -1;
	while (++i < map->height)
	{
		if ((map->matrix[i][0] != '1' && map->matrix[i][0] != ' ') ||
			(map->matrix[i][map->width - 1] != '1' &&
			map->matrix[i][map->width - 1] != ' '))
			return (printf("Error\nInvalid char at side border\n"), 0);
	}
	return (1);
}

int	validate_map(t_map *map)
{
	if (!map || !map->matrix)
		return (printf("Error\nMap matrix missing\n"), 0);
	if (map->height <= 0 || map->width <= 0)
		return (printf("Error\nInvalid map dimensions\n"), 0);
	if (!check_borders(map))
		return (0);
	if (!find_player(map))
		return (0);
	if (!check_leaks(map))
		return (0);
	return (1);
}
