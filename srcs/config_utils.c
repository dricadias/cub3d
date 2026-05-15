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

	if (!line || !*line)
		return (-1);
	rgb = ft_split(line, ',');
	if (!rgb)
		return (printf("Error\nMemory alloc. for color parsing\n"), -1);
	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		printf("Error\nInvalid color format\n");
		free_matrix(rgb);
		return (-1);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free_matrix(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (printf("Error\nRGB values must be between 0 and 255\n"), -1);
	return (create_rgb(r, g, b));
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
		return (printf("Error\nMemory alloc. for texture path\n"), NULL);
	return (result);
}

static int	set_texture(char **dst, char *line, int n, char *name)
{
	if (*dst)
		return (printf("Error\nDuplicate %s identifier\n", name), 0);
	*dst = skip_prefix(line, n);
	if (!*dst)
		return (0);
	return (1);
}

int	handle_identifier(t_map *map, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (set_texture(&map->no_path, line, 3, "NO"));
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (set_texture(&map->so_path, line, 3, "SO"));
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (set_texture(&map->we_path, line, 3, "WE"));
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (set_texture(&map->ea_path, line, 3, "EA"));
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (map->floor_color != -1)
			return (printf("Error\nDuplicate F identifier\n"), 0);
		map->floor_color = parse_color(line + 2);
		return (map->floor_color != -1);
	}
	if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (map->ceiling_color != -1)
			return (printf("Error\nDuplicate C identifier\n"), 0);
		map->ceiling_color = parse_color(line + 2);
		return (map->ceiling_color != -1);
	}
	return (1);
}
