/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 15:02:48 by adias-do          #+#    #+#             */
/*   Updated: 2026/05/09 12:55:50 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

typedef struct s_pos
{
	double	x;
	double	y;
}	t_pos;

" i feel like this should exist, dont now yet how to defin
typedef struct dir_vector
{
	its t_pos +('+' ou '-')
}  ;
  "
typedef struct	s_map
{
	int		width;
	int		height;
	char	**matrix;
	t_pos	player_pos;
	char	player_dir;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor_color;
	int		ceiling_color;
}	t_map;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_ray
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
}	t_ray;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_map		map;
	t_player	player;
	t_texture	north;
	t_texture	south;
	t_texture	east;
	t_texture	west;
}	t_game;


// =========================================================
// PARSER E VALIDAÇÃO
// =========================================================
char		**read_file(char *filename);
char		*get_next_line(int fd);
void		gnl_cleanup(void);

void		parse_config(t_map *map, char **file);
int			valid_config(t_map *map);

int			is_map(char *line);
int			map_index(char **file);
void		built_map(t_game *game, char **file, int start);
int			map_width(char **file, int start);
int			map_height(char **file, int start);
char		*spaces_in_line(char *line, int width);

int			validate_map(t_map *map);
int			check_borders(t_map *map);
int			find_player(t_map *map);
int			is_player(char c);
int			check_leaks(t_map *map);

void		init_player(t_game *game);
void		init_game(t_game *game);

void		free_file(char **file);
void		free_map(t_map *map);
void		free_split(char **arr);
void		free_config(t_map *map);
void		cleanup_game(t_game *game, char **file, int free_file_flag);


// =========================================================
// RAYCASTING E RENDERIZAÇÃO
// =========================================================
void		load_texture(void *mlx, t_texture *tex, char *path);
void		free_texture(void *mlx, t_texture *tex);

int			render(t_game *game);
void		pixel_put(t_img *data, int x, int y, int color);
void		draw_column(t_game *game, t_ray *ray, int x);
t_texture	*get_wall_texture(t_game *game, t_ray *ray);
int			get_tex_color(t_texture *tex, int x, int y);
int			calc_tex_x(t_game *game, t_ray *ray, t_texture *current_tex);

void		cast_ray(t_player *player, t_map *map, t_ray *ray, int x);

"typedef struct player
{
	t_pos *init_pos; 
	dir_vector *looking
	#camera width definitions... raycasting FOV (vai ser sempre o mesmo, podemos usar rato aumentar/diminuir (isto é capaz de ser uma pain in the ass por causa de minilibx rendering images))

}"

#endif