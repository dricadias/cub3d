/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anferrei <anferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 13:52:11 by anferrei          #+#    #+#             */
/*   Updated: 2026/04/09 13:52:11 by anferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	parse_config(t_map *map, char **file)
{
	int	i;

	if (!map || !file)
		return (printf("Error\nInvalid parameters\n"), (void)0);
	map->no_path = NULL;
	map->so_path = NULL;
	map->we_path = NULL;
	map->ea_path = NULL;
	map->floor_color = -1;
	map->ceiling_color = -1;
	i = 0;
	while (file[i])
	{
		if (!handle_identifier(map, file[i]))
			return ;
		i++;
	}
}

int	valid_config(t_map *map)
{
	if (!map)
		return (printf("Error\nInvalid map pointer\n"), 0);
	if (!map->no_path)
		return (printf("Error\nMissing NO (North) texture\n"), 0);
	if (!map->so_path)
		return (printf("Error\nMissing SO (South) texture\n"), 0);
	if (!map->we_path)
		return (printf("Error\nMissing WE (West) texture\n"), 0);
	if (!map->ea_path)
		return (printf("Error\nMissing EA (East) texture\n"), 0);
	if (map->floor_color == -1)
		return (printf("Error\nInvalid or missing F (floor) color\n"), 0);
	if (map->ceiling_color == -1)
		return (printf("Error\nInvalid or missing C (ceiling) color\n"), 0);
	return (1);
}
