/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 05:12:18 by blatifat          #+#    #+#             */
/*   Updated: 2024/09/13 13:46:09 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_game(t_data *data)
{
	t_mlx	mlx;

	mlx.data = data;
	mlx.ply = calloc(1, sizeof(t_player));
	mlx.ray = calloc(1, sizeof(t_ray));
	mlx.mlx_ptr = mlx_init(S_W, S_H, "Cub3D", 0);
	if (mlx.mlx_ptr == NULL)
	{
		printf("Failed to initialize MLX\n");
		return ;
	}
	// game_init(&mlx);
	player_init(&mlx);
	mlx_loop_hook(mlx.mlx_ptr, &game_loop, &mlx);
	mlx_key_hook(mlx.mlx_ptr, &mlx_key, &mlx);
	mlx_loop(mlx.mlx_ptr);
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