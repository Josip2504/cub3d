/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 05:12:18 by blatifat          #+#    #+#             */
/*   Updated: 2024/10/16 22:22:32 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	initiation(t_mlx *mlx)
{
	mlx->ply = (t_player *)malloc(sizeof(t_player));
	mlx->ray = (t_ray *)malloc(sizeof(t_ray));
	mlx->textur = (t_texture *)malloc(sizeof(t_texture));
	mlx->data = NULL;
	mlx->map = NULL;
	mlx->imgage = NULL;
	mlx->mlx_ptr = NULL;
	if (mlx->textur)
	{
		mlx->textur->east = NULL;
		mlx->textur->north = NULL;
		mlx->textur->west = NULL;
		mlx->textur->south = NULL;
	}
}

void	init_game(t_data *data, t_map *map)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
	{
		ft_printf("Memory allocation failed\n");
		return ;
	}
	initiation(mlx);
	mlx->data = data;
	mlx->mlx_ptr = mlx_init(S_W, S_H, "Cub3D", true);
	if (mlx->mlx_ptr == NULL)
	{
		ft_printf("Failed to initialize MLX\n");
		return ;
	}
	load_texture(mlx, map);
	player_init(mlx, data, map);
	mlx_loop_hook(mlx->mlx_ptr, &game_loop, mlx);
	mlx_key_hook(mlx->mlx_ptr, &mlx_key, mlx);
	mlx_loop(mlx->mlx_ptr);
}
