/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 05:11:13 by blatifat          #+#    #+#             */
/*   Updated: 2024/10/03 04:15:21 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	handle_key_press(t_mlx *mlx, int key)
{
	if (key == MLX_KEY_A)
		mlx->ply->left_right = -1;
	else if (key == MLX_KEY_D)
		mlx->ply->left_right = 1;
	else if (key == MLX_KEY_W)
		mlx->ply->up_down = 1;
	else if (key == MLX_KEY_S)
		mlx->ply->up_down = -1;
	else if (key == MLX_KEY_LEFT)
		mlx->ply->rotation = -1;
	else if (key == MLX_KEY_RIGHT)
		mlx->ply->rotation = 1;
}

void	handle_key_release(t_mlx *mlx, int key)
{
	if (key == MLX_KEY_A || key == MLX_KEY_D)
		mlx->ply->left_right = 0;
	else if (key == MLX_KEY_W || key == MLX_KEY_S)
		mlx->ply->up_down = 0;
	else if (key == MLX_KEY_LEFT || key == MLX_KEY_RIGHT)
		mlx->ply->rotation = 0;
}

void	mlx_key(mlx_key_data_t keydata, void *ml)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)ml;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		exit_game(mlx);
	else if (keydata.action == MLX_PRESS)
		handle_key_press(mlx, keydata.key);
	else if (keydata.action == MLX_RELEASE)
		handle_key_release(mlx, keydata.key);
}
