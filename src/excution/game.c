/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 05:12:18 by blatifat          #+#    #+#             */
/*   Updated: 2024/09/23 17:08:12 by jsamardz         ###   ########.fr       */
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
	mlx->ply->rotation = 0;
	mlx->ply->left_right = 0;
	mlx->ply->up_down = 0;
	mlx->ray->angle = 0;
	mlx->ray->distance = 0;
	mlx->ray->wall_flag = 0;
	mlx->ray->index = 0;
}

void	init_game(t_data *data, t_map *map)
{	
	t_mlx *mlx = malloc(sizeof(t_mlx));  // Allocate memory here

	if (!mlx)
	{
		printf("Memory allocation failed\n");
		return;
	}
	initiation(mlx);
	mlx->data = data;
	mlx->mlx_ptr = mlx_init(S_W, S_H, "Cub3D", 0);
	if (mlx->mlx_ptr == NULL)
	{
		printf("Failed to initialize MLX\n");
		return ;
	}
	load_texture(mlx, map);
	player_init(mlx, data);
	mlx_loop_hook(mlx->mlx_ptr, &game_loop, mlx);
	mlx_key_hook(mlx->mlx_ptr, &mlx_key, mlx);			// OK
	mlx_loop(mlx->mlx_ptr);
}

/* void	init_game(t_data *dt)
{
	t_mlx	mlx;

	game_init(&mlx);
	mlx.data = dt;
	mlx.mlx_ptr = mlx_init(S_W, S_H, "Cub3D", 0);
	load_texture(&mlx);
	init_the_player(&mlx);
	mlx_loop_hook(mlx.mlx_ptr, &game_loop, &mlx);
	mlx_key_hook(mlx.mlx_ptr, &mlx_key, &mlx);
	mlx_loop(mlx.mlx_ptr);  // Enter mlx loop
	free_game_struct(&mlx);
}
 */