/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:34:42 by blatifat          #+#    #+#             */
/*   Updated: 2024/10/07 14:57:51 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <errno.h>
# include "../libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

# define S_W 1900
# define S_H 1000
# define TILE_SIZE 15
# define FOV 60
# define ROTATION_SPEED 0.045
# define PLAYER_SPEED 4
# define MLX_CLOSE 17

# define WRONG_ARGS_NUM 1
# define NAME_LENGTH 2
# define WRONG_EXTENSION 3
# define FILE_OPEN 4
# define MAP_DESCRIPTION 5
# define INVALID_MAP 6
# define LOAD_TEXTURES 7

# define NORTH 4.71238898038
# define EAST 0.0
# define SOUTH 1.57079632679
# define WEST 6.28318530718

# define RED 0
# define GREEN 1
# define BLUE 2

typedef struct s_player
{
	int		player_x;
	int		player_y;
	double	ply_angle;
	float	fov;
	int		rotation;
	int		left_right;
	int		up_down;
}	t_player;

typedef struct s_ray
{
	double	angle;
	double	distance;
	double	hor_x;
	double	hor_y;
	int		wall_flag;
	int		index;
}	t_ray;

typedef struct s_map
{
	int		map_width;
	int		map_height;
	char	**map2d;
	int		arg_c;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
	int		player_x;
	int		player_y;
	int		player_count;
	char	player;
}	t_map;

typedef struct s_data
{
	char	**map2d;
	int		ply_x;
	int		ply_y;
	int		width_map;
	int		height_map;
	int		ceil[3];
	int		floor[3];
	t_map	*map;
}	t_data;

typedef struct s_texture
{
	mlx_texture_t	*east;
	mlx_texture_t	*west;
	mlx_texture_t	*south;
	mlx_texture_t	*north;
}	t_texture;

typedef struct s_mlx
{
	mlx_image_t	*imgage;
	mlx_t		*mlx_ptr;
	t_ray		*ray;
	t_data		*data;
	t_player	*ply;
	t_texture	*textur;
	t_map		*map;
}	t_mlx;

typedef struct s_wall_params
{
	double	top_pixel;
	double	bottom_pixel;
	double	wall_height;
	int		ray;
}	t_wall_params;

typedef struct s_texture_params
{
	double			x_offset;
	double			y_offset;
	double			scale_factor;
	mlx_texture_t	*texture;
}	t_texture_params;

void			exit_game(t_mlx *mlx);
void			mlx_key(mlx_key_data_t keydata, void *ml);
void			hook_mvt(t_mlx *mlx);
void			render_wall_and_floor(t_mlx *mlx, int ray);
void			init_game(t_data *data, t_map *map);
void			cast_rays(t_mlx *mlx);
void			free_game(t_mlx *mlx);
int				verify_circle(float angle, char c);
int				evaluate_intersection(float angle, float *inter,
					float *step, int horiz);
void			game_loop(void *param);
void			player_init(t_mlx *mlx, t_data *data, t_map *map);
void			free_dbl_char(char **array);
void			free_ptr(void *ptr);
void			free_textures(t_texture *tex);
void			load_texture(t_mlx *mlx, t_map *map);
uint32_t		rgb_color(int r, int g, int b, int a);
void			ft_put_pixel(t_mlx *mlx, int x, int y, int color);
unsigned int	get_color(int c);
double			get_x_offset(mlx_texture_t *texture, t_mlx *mlx);
int				error(int errnum);
// utils.c
void			error_exit(t_map *map, char *s);
void			my_sscanf(char *str, int *a, int *b, int *c);
void			line_check(t_map *map, char *line);
void			free_map(t_map *map, int i);
// init.c
void			init(t_map *map);
// read_map.c
void			read_map(t_map *map, char **argv);
int				correct_arg(const char *name);
void			check_wall(t_map *map, int i, int j);
// store_map.c
void			store_map(t_map *map, char **argv);
void			valid_map(t_map *map);
// transfer.c
t_data			*transfer_data(t_map *map);
char			*trim(t_map *map, char *s);
// utils2.c
int				ft_isspace(char c);
void			cop(int i, int j, char *s, char *res);
void			store_player(t_map *map);
void			char_check(t_map *map, char *line);
void			error_exit_nofree(char *s);

#endif