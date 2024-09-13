/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 06:33:59 by blatifat          #+#    #+#             */
/*   Updated: 2024/09/13 16:49:57 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	load_texture(t_mlx *mlx)
{
	mlx->textur->east = mlx_load_png(mlx->data->map->ea);
	mlx->textur->south = mlx_load_png(mlx->data->map->so);
	mlx->textur->north = mlx_load_png(mlx->data->map->no);
	mlx->textur->west = mlx_load_png(mlx->data->map->we);

	if (!mlx->textur->east || !mlx->textur->south
		|| !mlx->textur->north || !mlx->textur->west)
	{
		free_game(mlx);
		/* error(LOAD_TEXTURES); */
	}
}

void	game_loop(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (mlx->imgage != NULL)
		mlx_delete_image(mlx->mlx_ptr, mlx->imgage);
	mlx->imgage = mlx_new_image(mlx->mlx_ptr, S_W, S_H);
	if (mlx->imgage == NULL)
	{
		printf("Failed to create a new image\n");
		return ;
	}
	hook_mvt(mlx);
	cast_rays(mlx);
	mlx_image_to_window(mlx->mlx_ptr, mlx->imgage, 0, 0);
}


void	player_init(t_mlx *mlx)
{
	mlx->ply->player_x = (mlx->data->ply_x * TILE_SIZE) + (TILE_SIZE / 2);
	mlx->ply->player_y = (mlx->data->ply_y * TILE_SIZE) + (TILE_SIZE / 2);
	mlx->ply->fov = (FOV * M_PI) / 180;
	mlx->ply->angle = M_PI;
}

void	game_init(t_mlx *mlx)
{
	*mlx = (t_mlx)
	{
		.ply = calloc(1, sizeof(t_player)),
		.ray = calloc(1, sizeof(t_ray)),
		.textur = calloc(1, sizeof(t_texture)),
		.data = NULL,
		.imgage = NULL
	};
	mlx->textur->east = NULL;
	mlx->textur->west = NULL;
	mlx->textur->south = NULL;
	mlx->textur->north = NULL;
}