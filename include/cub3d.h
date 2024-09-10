/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:34:42 by blatifat          #+#    #+#             */
/*   Updated: 2024/09/10 15:08:56 by jsamardz         ###   ########.fr       */
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


typedef struct s_player
{
	double		player_x;
	double		player_y;
	double		angle;
	float		fov;
	int			rotation;
	int			left_right;
	int			up_down;
}	t_player;

typedef struct s_ray // the ray structure
{
	double	ray_angel;
	double	distance;
	int		wall_flag;
}	t_ray;

typedef struct s_map {
	int		player_x;
	int		player_y;
	int		map_width;
	int		map_height;
	int		ceiling[3];
	int		floor[3];
	char	**map2d;
	int		arg_c;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
}	t_map;
typedef struct s_game // the data structure
{
	mlx_t				*mlx;
	mlx_texture_t		*up;
	mlx_texture_t		*down;
	mlx_texture_t		*left;
	mlx_texture_t		*right;
	t_player			*player;
	t_map				*map;
	t_ray				*ray;
	mlx_image_t			*image;
}	t_game;

typedef struct s_mlx // the mlx structure
{
	mlx_image_t	*image;
	mlx_t		*mlx_ptr;
	t_ray		*ray;
	t_game		*game;
	t_player	*player;
}	t_mlx;

typedef struct s_wall_params
{
	double top_pixel;
	double bottom_pixel;
	double wall_height;
	int ray;
}	t_wall_params;

void start_the_game(t_game *data);
void my_key_callback(struct mlx_key_data key_data, void *param);
void hook(t_mlx *mlx, int arg1, int arg2);
void cast_rays(t_mlx *mlx);
void handle_keypress(mlx_key_data_t keydata, void *ml);
void ft_exit(t_mlx *mlx);
/* void init_player(t_game *game, char orientation); */
void	error_exit(char *s);
double	find_v_intersection(double ray_angle, t_game *game);
double	find_h_intersection(double ray_angle, t_game *game);
void	rays_cast(t_game *game, t_mlx *mlx);
void	free_textures(t_game *game);
void	free_game_struct(t_game *game);
void	free_mlx_struct(t_mlx *mlx);
void	free_map(t_map *map);
double	normaliz_angle(double angle);
void	init_player(t_game *game, char orientation);
int		wall_hit(double x, double y, t_game *game);
void	laod_textures(t_game *game);
void	key_callback(mlx_key_data_t keydata, void *param);
void	render_wall(t_game *game, t_mlx *mlx, int ray);
mlx_texture_t	*wall_texture(t_game *game, int wall_side);
void	input_handler(mlx_key_data_t keydata, void *param);
void	laod_textures(t_game *game);
void free_game_resources(t_game *game);
void	game_loop(void *param);
void start_game(t_game *game, char orientation);
void	move_player(t_game *game);

typedef struct	s_data
{
	char	player;
	int		player_count;
	int		player_x;
	int		player_y;
	t_map	*map;
}	t_data;

// utils.c
void	error_exit(char *s);

// init.c
void	init(t_data *data);

// read_map.c
void	read_map(t_data *data, char **argv);

// store_map.c
void	store_map(t_data *data, char **argv);
void	valid_map(t_data *data);

#endif