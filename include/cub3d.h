/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:34:42 by blatifat          #+#    #+#             */
/*   Updated: 2024/09/17 13:14:51 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "../libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

# define S_W 1900
# define S_H 1000
# define TILE_SIZE 30
# define FOV 60
# define ROTATION_SPEED 0.045
# define PLAYER_SPEED 4
# define MLX_CLOSE 17

# define RED 0
# define GREEN 1
# define BLUE 2

typedef struct	s_player
{
	int		player_x;
	int		player_y;
	double	angle;
	float	fov;
	int		rotation;
	int		left_right;
	int		up_down;
}	t_player;

typedef struct s_ray
{
	double	angle;
	double	distance;
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

typedef struct s_game
{
	mlx_texture_t	*east;
	mlx_texture_t	*west;
	mlx_texture_t	*south;
	mlx_texture_t	*north;
}	t_texture;

typedef struct	s_mlx
{
	mlx_image_t	*imgage;
	mlx_t		*mlx_ptr;
	t_ray		*ray;
	t_data		*data;
	t_player	*ply;
	t_texture	*textur;
}	t_mlx;

typedef struct s_wall_params
{
	double	top_pixel;
	double	bottom_pixel;
	double	wall_height;
	int		ray;
}	t_wall_params;

void	game_init(t_mlx *mlx);
void	exit_game(t_mlx *mlx);
void	mlx_key(mlx_key_data_t keydata, void *ml);
void	hook_mvt(t_mlx *mlx);
void	render_wall_and_floor(t_mlx *mlx, int ray);
void	init_game(t_data *data);
void	cast_rays(t_mlx *mlx);
void	free_game(t_mlx *mlx);
int		intersection_checking(float angle, float *inter,
			float *step, int is_horizon);
int		get_unit_circle(float angle, char c);
void	game_loop(void *param);
void	player_init(t_mlx *mlx);
void	free_dbl_char(char **array);
void	free_ptr(void *ptr);
void	free_textures(t_texture *tex);

// utils.c
void	error_exit(char *s);
int		ft_isspace(char c);
void	my_sscanf(char *str, int *a, int *b, int *c);
void	line_check(char *line);

// init.c
void	init(t_map *map);

// read_map.c
void	read_map(t_map *map, char **argv);

// store_map.c
void	store_map(t_map *map, char **argv);
void	valid_map(t_map *map);

// transfer.c
t_data	*transfer_data(t_map *map);
void	store_player(t_map *map);
char	*trim(char *s);

#endif