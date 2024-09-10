/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 05:11:13 by blatifat          #+#    #+#             */
/*   Updated: 2024/09/07 04:36:52 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	player_move(t_game *game, int direction)
{
	double	move_step;
	double	new_x;
	double	new_y;

	move_step = direction * PLAYER_SPEED;
	new_x = game->player->player_x + cos(game->player->angle) * move_step;
	new_y = game->player->player_y + sin(game->player->angle) * move_step;
	if (!wall_hit(new_x, new_y, game))
	{
		game->player->player_x = new_x;
		game->player->player_x = new_y;
	}
}

void	player_rotate(t_game *game, double angle_rotation)
{
	game->player->angle += angle_rotation;
	if (game->player->angle < 0)
		game->player->angle += 2 * M_PI;
	else if (game->player->angle >= 2 * M_PI)
		game->player->angle -= 2 * M_PI;
}

void	key_callback(mlx_key_data_t keydata, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (keydata.key == MLX_KEY_W)
		player_move(mlx->game, 1);
	else if (keydata.key == MLX_KEY_S)
		player_move(mlx->game, -1);
	else if (keydata.key == MLX_KEY_A)
		player_rotate(mlx->game, -ROTATION_SPEED);
	else if (keydata.key == MLX_KEY_D)
		player_rotate(mlx->game, -ROTATION_SPEED);
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(mlx->mlx_ptr);
}

void	laod_textures(t_game *game)
{
	game->up = mlx_load_png("path_to_north_texture.png");
	game->down = mlx_load_png("path_to_south_texture.png");
	game->left = mlx_load_png("path_to_west_texture.png");
	game->right = mlx_load_png("path_to_east_texture.png");
	if (!game->up || game->down || game->left || game->right)
		error_exit("Fail to load textures");
}

mlx_texture_t	*wall_texture(t_game *game, int wall_side)
{
	if (wall_side == 0)
		return (game->right);
	else
		return (game->up);
}

/* void	render_wall(t_mlx *mlx, int ray_id, double distance)
{
	int	wall_height;
	int	wall_start;
	int	wall_end;
	int	y ;

	wall_height = (TILE_SIZE / distance) * (S_H / 2);
	wall_start = (S_H / 2) - (wall_height / 2);
	wall_end = (S_H / 2) + (wall_height / 2);

	if (wall_start < 0)
		wall_start = 0;
	if (wall_end >= S_H)
		wall_end = S_H - 1;
	y = wall_start;
	while (y <= wall_end)
	{
		mlx_put_pixel(mlx->image, ray_id, y, 0xFFFFFF);
		y++;
	}
} */