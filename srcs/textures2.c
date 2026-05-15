/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:32:52 by adias-do          #+#    #+#             */
/*   Updated: 2026/05/15 15:34:12 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	check_texture_params(void *mlx, t_texture *tex, char *path)
{
	if (!mlx || !tex || !path)
	{
		printf("Error\nInvalid parameters for texture loading\n");
		exit(1);
	}
	if (!*path)
	{
		printf("Error\nEmpty texture path\n");
		exit(1);
	}
}

static void	get_texture_data(void *mlx, t_texture *tex, char *path)
{
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	if (!tex->addr)
	{
		printf("Error\nFailed to get texture data address: %s\n", path);
		mlx_destroy_image(mlx, tex->img);
		tex->img = NULL;
		exit(1);
	}
	if (tex->bpp <= 0 || tex->line_len <= 0)
	{
		printf("Error\nTexture has invalid data format: %s\n", path);
		mlx_destroy_image(mlx, tex->img);
		tex->img = NULL;
		tex->addr = NULL;
		exit(1);
	}
}

void	load_texture(void *mlx, t_texture *tex, char *path)
{
	check_texture_params(mlx, tex, path);
	tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img)
	{
		printf("Error\nTexture load: %s (file not found/inv. format)\n", path);
		exit(1);
	}
	if (tex->width <= 0 || tex->height <= 0)
	{
		printf("Error\nTexture has invalid dimensions: %s (w=%d, h=%d)\n",
			path, tex->width, tex->height);
		mlx_destroy_image(mlx, tex->img);
		tex->img = NULL;
		exit(1);
	}
	get_texture_data(mlx, tex, path);
}
