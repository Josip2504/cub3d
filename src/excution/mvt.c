/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 05:11:50 by blatifat          #+#    #+#             */
/*   Updated: 2024/10/16 12:36:18 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	player_rotation(t_mlx *mlx)
{
	if (mlx->ply->rotation == 1)
	{
		mlx->ply->ply_angle += ROTATION_SPEED;
		if (mlx->ply->ply_angle > 2 * M_PI)
			mlx->ply->ply_angle -= 2 * M_PI;
	}
	else if (mlx->ply->rotation == -1)
	{
		mlx->ply->ply_angle -= ROTATION_SPEED;
		if (mlx->ply->ply_angle < 0)
			mlx->ply->ply_angle += 2 * M_PI;
	}
}

void	move_player(t_mlx *mlx, double move_x, double move_y)
{
	int		map_grid_x;
	int		map_grid_y;
	char	c;

	map_grid_x = (int)(mlx->ply->player_x + move_x) / TILE_SIZE;
	map_grid_y = (int)(mlx->ply->player_y + move_y) / TILE_SIZE;
	c = mlx->data->map2d[map_grid_y][map_grid_x];
	if (c != '1')
	{
		mlx->ply->player_x += move_x;
		mlx->ply->player_y += move_y;
	}
}

void	process_player_movement(t_mlx *mlx, int move_x, int move_y)
{
	if (mlx->ply->up_down == 1)
	{
		move_x = cos(mlx->ply->ply_angle) * PLAYER_SPEED;
		move_y = sin(mlx->ply->ply_angle) * PLAYER_SPEED;
	}
	else if (mlx->ply->left_right == 1)
	{
		move_x = -sin(mlx->ply->ply_angle) * PLAYER_SPEED;
		move_y = cos(mlx->ply->ply_angle) * PLAYER_SPEED;
	}
	else if (mlx->ply->left_right == -1)
	{
		move_x = sin(mlx->ply->ply_angle) * PLAYER_SPEED;
		move_y = -cos(mlx->ply->ply_angle) * PLAYER_SPEED;
	}
	else if (mlx->ply->up_down == -1)
	{
		move_x = -cos(mlx->ply->ply_angle) * PLAYER_SPEED;
		move_y = -sin(mlx->ply->ply_angle) * PLAYER_SPEED;
	}
	move_player(mlx, move_x, move_y);
}

void	hook_mvt(t_mlx *mlx)
{
	int	move_x;
	int	move_y;

	move_x = 0;
	move_y = 0;
	player_rotation(mlx);
	process_player_movement(mlx, move_x, move_y);
}
