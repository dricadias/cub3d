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

static int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

static int	parse_color(char *line)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;
	int		result;

	if (!line || !*line)
		return (-1);
	rgb = ft_split(line, ',');
	if (!rgb)
	{
		printf("Error\nMemory allocation failed for color parsing\n");
		return (-1);
	}
	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		printf("Error\nInvalid color format: expected R,G,B (3 values)\n");
		free_split(rgb);
		return (-1);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free_split(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		printf("Error\nRGB values must be between 0 and 255\n");
		return (-1);
	}
	result = create_rgb(r, g, b);
	return (result);
}

static char	*skip_prefix(char *line, int n)
{
	char	*result;

	if (!line)
		return (NULL);
	while (line[n] && line[n] == ' ')
		n++;
	result = ft_strdup(line + n);
	if (!result)
	{
		printf("Error\nMemory allocation failed for texture path\n");
		return (NULL);
	}
	return (result);
}

void	parse_config(t_map *map, char **file)
{
	int	i;

	if (!map || !file)
	{
		printf("Error\nInvalid parameters for config parsing\n");
		return ;
	}
	map->no_path = NULL;
	map->so_path = NULL;
	map->we_path = NULL;
	map->ea_path = NULL;
	map->floor_color = -1;
	map->ceiling_color = -1;
	i = 0;
	while (file[i])
	{
		if (ft_strncmp(file[i], "NO ", 3) == 0)
		{
			if (map->no_path)
			{
				printf("Error\nDuplicate NO identifier\n");
				return ;
			}
			map->no_path = skip_prefix(file[i], 3);
			if (!map->no_path)
				return ;
		}
		else if (ft_strncmp(file[i], "SO ", 3) == 0)
		{
			if (map->so_path)
			{
				printf("Error\nDuplicate SO identifier\n");
				return ;
			}
			map->so_path = skip_prefix(file[i], 3);
			if (!map->so_path)
				return ;
		}
		else if (ft_strncmp(file[i], "WE ", 3) == 0)
		{
			if (map->we_path)
			{
				printf("Error\nDuplicate WE identifier\n");
				return ;
			}
			map->we_path = skip_prefix(file[i], 3);
			if (!map->we_path)
				return ;
		}
		else if (ft_strncmp(file[i], "EA ", 3) == 0)
		{
			if (map->ea_path)
			{
				printf("Error\nDuplicate EA identifier\n");
				return ;
			}
			map->ea_path = skip_prefix(file[i], 3);
			if (!map->ea_path)
				return ;
		}
		else if (ft_strncmp(file[i], "F ", 2) == 0)
		{
			if (map->floor_color != -1)
			{
				printf("Error\nDuplicate F identifier\n");
				return ;
			}
			map->floor_color = parse_color(file[i] + 2);
		}
		else if (ft_strncmp(file[i], "C ", 2) == 0)
		{
			if (map->ceiling_color != -1)
			{
				printf("Error\nDuplicate C identifier\n");
				return ;
			}
			map->ceiling_color = parse_color(file[i] + 2);
		}
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
