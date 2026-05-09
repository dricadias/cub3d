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

//get a way to divide, maybe by generalizing the error messages!
int	check_leaks(t_map *map)
{
	int	x;
	int	y;

	if (!map || !map->matrix)
	{
		printf("Error\nInvalid map for leak check\n");
		return (0);
	}
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->matrix[y][x] == '0'
				|| is_player(map->matrix[y][x]))
			{
				if (y == 0 || y == map->height - 1
					|| x == 0 || x == map->width - 1)
				{
					printf("Error\nMap is not enclosed (open space at edge)\n");
					return (0);
				}
				if (y > 0 && map->matrix[y - 1][x] == ' ')
				{
					printf("Error\nMap has leaks (open space above at y=%d, x=%d)\n", y, x);
					return (0);
				}
				if (y < map->height - 1 && map->matrix[y + 1][x] == ' ')
				{
					printf("Error\nMap has leaks (open space below at y=%d, x=%d)\n", y, x);
					return (0);
				}
				if (x > 0 && map->matrix[y][x - 1] == ' ')
				{
					printf("Error\nMap has leaks (open space left at y=%d, x=%d)\n", y, x);
					return (0);
				}
				if (x < map->width - 1 && map->matrix[y][x + 1] == ' ')
				{
					printf("Error\nMap has leaks (open space right at y=%d, x=%d)\n", y, x);
					return (0);
				}
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	find_player(t_map *map)
{
	int	x;
	int	y;
	int	count;

	if (!map || !map->matrix)
	{
		printf("Error\nInvalid map for player search\n");
		return (0);
	}
	count = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (is_player(map->matrix[y][x]))
			{
				map->player_pos.x = x + 0.5;
				map->player_pos.y = y + 0.5;
				map->player_dir = map->matrix[y][x];
				count++;
			}
			x++;
		}
		y++;
	}
	if (count == 0)
	{
		printf("Error\nNo player found in map\n");
		return (0);
	}
	if (count > 1)
	{
		printf("Error\nMultiple players found in map (%d)\n", count);
		return (0);
	}
	return (1);
}

int	check_borders(t_map *map)
{
	int	x;
	int	y;

	if (!map || !map->matrix)
	{
		printf("Error\nInvalid map for border check\n");
		return (0);
	}
	if (map->height <= 0 || map->width <= 0)
	{
		printf("Error\nMap has invalid dimensions\n");
		return (0);
	}
	x = 0;
	while (x < map->width)
	{
		if (map->matrix[0][x] != '1' && map->matrix[0][x] != ' ')
		{
			printf("Error\nInvalid character at top border (y=0, x=%d): '%c'\n",
				x, map->matrix[0][x]);
			return (0);
		}
		if (map->matrix[map->height - 1][x] != '1'
			&& map->matrix[map->height - 1][x] != ' ')
		{
			printf("Error\nInvalid character at bottom border (y=%d, x=%d): '%c'\n",
				map->height - 1, x, map->matrix[map->height - 1][x]);
			return (0);
		}
		x++;
	}
	y = 0;
	while (y < map->height)
	{
		if (map->matrix[y][0] != '1' && map->matrix[y][0] != ' ')
		{
			printf("Error\nInvalid character at left border (y=%d, x=0): '%c'\n",
				y, map->matrix[y][0]);
			return (0);
		}
		if (map->matrix[y][map->width - 1] != '1'
			&& map->matrix[y][map->width - 1] != ' ')
		{
			printf("Error\nInvalid character at right border (y=%d, x=%d): '%c'\n",
				y, map->width - 1, map->matrix[y][map->width - 1]);
			return (0);
		}
		y++;
	}
	return (1);
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
