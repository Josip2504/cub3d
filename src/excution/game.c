/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 05:12:18 by blatifat          #+#    #+#             */
/*   Updated: 2024/09/30 14:12:27 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void initiation(t_mlx *mlx)
{
	mlx->ply = malloc(sizeof(t_player));
	mlx->ray = malloc(sizeof(t_ray));
	mlx->textur = malloc(sizeof(t_texture));
	mlx->data = NULL;
	mlx->map = NULL;
	mlx->imgage = NULL;
	mlx->mlx_ptr = NULL;
	mlx->textur->east = NULL;
	mlx->textur->north = NULL;
	mlx->textur->west = NULL;
	mlx->textur->south = NULL;
}

void	init_game(t_data *data, t_map *map)
{	
	t_mlx *mlx = malloc(sizeof(t_mlx));

	if (!mlx)
	{
		printf("Memory allocation failed\n");
		return;
	}
	initiation(mlx);
	mlx->data = data;
	mlx->mlx_ptr = mlx_init(S_W, S_H, "Cub3D", true);
	if (mlx->mlx_ptr == NULL)
	{
		printf("Failed to initialize MLX\n");
		return ;
	}
	load_texture(mlx, map);
	player_init(mlx, data, map);
	mlx_loop_hook(mlx->mlx_ptr, &game_loop, mlx);
	mlx_key_hook(mlx->mlx_ptr, &mlx_key, mlx);
	mlx_loop(mlx->mlx_ptr);
}
