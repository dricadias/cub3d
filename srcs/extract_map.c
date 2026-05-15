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

#include "../include/cub3d.h"

static void	get_map_size(char **file, int start, int *height, int *width)
{
	int	i;
	int	len;

	i = start;
	*height = 0;
	*width = 0;
	while (file[i])
	{
		len = ft_strlen(file[i]);
		if (len > *width)
			*width = len;
		(*height)++;
		i++;
	}
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

static int	fill_map_matrix(t_game *game, char **file, int start)
{
	int	i;
	int	j;

	i = 0;
	j = start;
	while (i < game->map.height)
	{
		game->map.matrix[i] = spaces_in_line(file[j], game->map.width);
		if (!game->map.matrix[i])
		{
			printf("Error\nMemory allocation failed for map row %d\n", i);
			free_partial_map(game->map.matrix, i);
			return (0);
		}
		i++;
		j++;
	}
	game->map.matrix[i] = NULL;
	return (1);
}

void	built_map(t_game *game, char **file, int start)
{
	if (!game || !file)
	{
		printf("Error\nInvalid parameters for map building\n");
		return ;
	}
	get_map_size(file, start, &game->map.height, &game->map.width);
	if (game->map.height <= 0 || game->map.width <= 0)
	{
		printf("Error\nInvalid map dimensions\n");
		return ;
	}
	game->map.matrix = malloc(sizeof(char *) * (game->map.height + 1));
	if (!game->map.matrix)
	{
		printf("Error\nMemory allocation failed for map matrix\n");
		return ;
	}
	if (!fill_map_matrix(game, file, start))
		game->map.matrix = NULL;
}
