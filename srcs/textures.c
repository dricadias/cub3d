/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 03:43:56 by adias-do          #+#    #+#             */
/*   Updated: 2026/05/09 14:22:47 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	load_texture(void *mlx, t_texture *tex, char *path)
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
	tex->img = mlx_xpm_file_to_image(mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
	{
		printf("Error\nTexture load: %s (file not found or inv. format)\n", path);
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
	tex->addr = mlx_get_data_addr(tex->img,
			&tex->bpp, &tex->line_len, &tex->endian);
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

t_texture	*get_wall_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (&game->east);
		else
			return (&game->west);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (&game->south);
		else
			return (&game->north);
	}
}

int	get_tex_color(t_texture *tex, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	dst = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}

int	calc_tex_x(t_game *game, t_ray *ray, t_texture *current_tex)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = game->player.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)current_tex->width);
	if (ray->side == 0 && ray->ray_dir_x < 0)
		tex_x = current_tex->width - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y > 0)
		tex_x = current_tex->width - tex_x - 1;
	return (tex_x);
}
