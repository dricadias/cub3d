/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anferrei <anferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 13:48:27 by anferrei          #+#    #+#             */
/*   Updated: 2026/04/09 13:48:27 by anferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anferrei <anferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 13:24:02 by anferrei          #+#    #+#             */
/*   Updated: 2026/04/09 13:24:02 by anferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	map_height(char **file, int start)
{
	int	i;
	int	count;

	i = start;
	count = 0;
	while (file[i])
	{
		count++;
		i++;
	}
	return (count);
}

int	map_width(char **file, int start)
{
	int	i;
	int	max;
	int	len;

	i = start;
	max = 0;
	while (file[i])
	{
		len = ft_strlen(file[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

char	*spaces_in_line(char *line, int width)
{
	char	*new;
	int		i;

	new = malloc(sizeof(char) * (width + 1));
	if (!new)
	{
		printf("Error\nMemory allocation failed for map line\n");
		return (NULL);
	}
	i = 0;
	while (line[i])
	{
		new[i] = line[i];
		i++;
	}
	while (i < width)
	{
		new[i] = ' ';
		i++;
	}
	new[i] = '\0';
	return (new);
}

static void	free_partial_map(char **matrix, int rows)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (i < rows)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

//to big of a function!!!!!
void	built_map(t_game *game, char **file, int start)
{
	int	i;
	int	j;

	if (!game || !file)
	{
		printf("Error\nInvalid parameters for map building\n");
		return ;
	}
	game->map.height = map_height(file, start);
	game->map.width = map_width(file, start);
	if (game->map.height <= 0 || game->map.width <= 0)
	{
		printf("Error\nInvalid map dimensions\n");
		game->map.matrix = NULL;
		return ;
	}
	game->map.matrix = malloc(sizeof(char *) * (game->map.height + 1));
	if (!game->map.matrix)
	{
		printf("Error\nMemory allocation failed for map matrix\n");
		game->map.matrix = NULL;
		return ;
	}
	i = 0;
	j = start;
	while (i < game->map.height)
	{
		game->map.matrix[i] = spaces_in_line(file[j], game->map.width);
		if (!game->map.matrix[i])
		{
			printf("Error\nMemory allocation failed for map row %d\n", i);
			free_partial_map(game->map.matrix, i);
			game->map.matrix = NULL;
			return ;
		}
		i++;
		j++;
	}
	game->map.matrix[i] = NULL;
}
