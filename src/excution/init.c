/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 06:33:59 by blatifat          #+#    #+#             */
/*   Updated: 2024/10/01 13:05:32 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	load_texture(t_mlx *mlx, t_map *map)
{	
	mlx->textur->east = mlx_load_png(map->ea);
	mlx->textur->south = mlx_load_png(map->so);
	mlx->textur->north = mlx_load_png(map->no);
	mlx->textur->west = mlx_load_png(map->we);
	if (!mlx->textur->east || !mlx->textur->south
		|| !mlx->textur->north || !mlx->textur->west)
	{
		printf("Error: Failed to load textures\n");
		free_game(mlx);
		error(LOAD_TEXTURES);
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

void	player_init(t_mlx *mlx, t_data *data, t_map *map)
{
	mlx->ply->player_x = (data->ply_x * TILE_SIZE) + (TILE_SIZE / 2);
	mlx->ply->player_y = (data->ply_y * TILE_SIZE) + (TILE_SIZE / 2);
	mlx->ply->fov = (FOV * M_PI) / 180;
	if (map->player == 'N')
		mlx->ply->angle = NORTH;
	else if (map->player == 'E')
		mlx->ply->angle = EAST;
	else if (map->player == 'W')
		mlx->ply->angle = WEST;
	else if (map->player == 'S')
		mlx->ply->angle = SOUTH;
}
