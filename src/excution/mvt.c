/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 05:11:50 by blatifat          #+#    #+#             */
/*   Updated: 2024/09/07 06:29:16 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	front_black_mvt(t_game *game, double move_step)
{
	double	new_x;
	double	new_y;

	new_x = game->player->player_x + cos(game->player->angle) * move_step;
	new_y = game->player->player_y + sin(game->player->angle) * move_step;
	if (!wall_hit(new_x, new_y, game))
	{
		game->player->player_x = new_x;
		game->player->player_y = new_y;
	}
}

void	left_right_mvt(t_game *game, double step_move)
{
	double	new_x;
	double	new_y;

	new_x = game->player->player_x
		+ cos(game->player->angle + M_PI_2) * step_move;
	new_y = game->player->player_y
		+ sin(game->player->angle + M_PI_2) * step_move;
	if (!wall_hit(new_x, new_y, game))
	{
		game->player->player_x = new_x;
		game->player->player_y = new_y;
	}
}

void	rotation_mvt(t_game *game, double rotation_angle)
{
	game->player->angle += rotation_angle;
	game->player->angle = normaliz_angle(game->player->angle);
}

void	input_handler(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_W)
		front_black_mvt(game, PLAYER_SPEED);
	else if (keydata.key == MLX_KEY_S)
		front_black_mvt(game, -PLAYER_SPEED);
	else if (keydata.key == MLX_KEY_A)
		left_right_mvt(game, -PLAYER_SPEED);
	else if (keydata.key == MLX_KEY_D)
		left_right_mvt(game, PLAYER_SPEED);
	else if (keydata.key == MLX_KEY_LEFT)
		rotation_mvt(game, -ROTATION_SPEED);
	else if (keydata.key == MLX_KEY_RIGHT)
		rotation_mvt(game, ROTATION_SPEED);
}

/* void game_loop(void *game_ptr)
{
    t_game *game = (t_game *)game_ptr;

    // Mise à jour de la position du joueur
    move_player(game);
    rotation_mvt(game);

    // Raycasting et rendu après déplacement
    rays_cast(game, game->mlx);

    // Mise à jour de l'affichage (s'il y a des images à afficher)
    mlx_image_to_window(game->mlx->mlx_ptr, game->mlx->image, 0, 0);
}
 */