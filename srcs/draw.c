/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 19:09:12 by adias-do          #+#    #+#             */
/*   Updated: 2026/05/09 14:21:55 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	calc_draw_limits(t_ray *ray, int *d)
{
	if (ray->perp_wall_dist < 0.01)
		ray->perp_wall_dist = 0.01;
	d[2] = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	d[3] = -d[2] / 2 + WIN_HEIGHT / 2;
	if (d[3] < 0)
		d[3] = 0;
	d[4] = d[2] / 2 + WIN_HEIGHT / 2;
	if (d[4] >= WIN_HEIGHT)
		d[4] = WIN_HEIGHT - 1;
}

static void	draw_pixels(t_game *g, t_ray *r, t_texture *tex, int *d)
{
	int		y;
	int		t_y;
	int		color;
	double	step;
	double	t_pos;

	step = 1.0 * tex->height / d[2];
	t_pos = (d[3] - WIN_HEIGHT / 2 + d[2] / 2) * step;
	y = 0;
	while (y < d[3])
		pixel_put(&g->img, d[0], y++, g->map.ceiling_color);
	while (y < d[4])
	{
		t_y = (int)t_pos % tex->height;
		if (t_y < 0)
			t_y = 0;
		t_pos += step;
		color = get_tex_color(tex, d[1], t_y);
		if (r->side == 1)
			color = (color >> 1) & 8355711;
		pixel_put(&g->img, d[0], y++, color);
	}
	while (y < WIN_HEIGHT)
		pixel_put(&g->img, d[0], y++, g->map.floor_color);
}

void	draw_column(t_game *game, t_ray *ray, int x)
{
	int			d[5];
	t_texture	*tex;

	d[0] = x;
	calc_draw_limits(ray, d);
	tex = get_wall_texture(game, ray);
	d[1] = calc_tex_x(game, ray, tex);
	if (d[1] >= tex->width)
		d[1] = tex->width - 1;
	if (d[1] < 0)
		d[1] = 0;
	draw_pixels(game, ray, tex, d);
}
