/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 06:33:59 by blatifat          #+#    #+#             */
/*   Updated: 2024/10/16 22:22:29 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	free_texture(t_map *map)
{
	if (map->no)
	{
		free(map->no);
		map->no = NULL;
	}
	if (map->so)
	{
		free(map->so);
		map->so = NULL;
	}
	if (map->we)
	{
		free(map->we);
		map->we = NULL;
	}
	if (map->ea)
	{
		free(map->ea);
		map->ea = NULL;
	}
}

void	load_texture(t_mlx *mlx, t_map *map)
{
	mlx->textur->east = mlx_load_png(map->we);
	mlx->textur->south = mlx_load_png(map->no);
	mlx->textur->north = mlx_load_png(map->so);
	mlx->textur->west = mlx_load_png(map->ea);
	free_texture(map);
	if (!mlx->textur->east || !mlx->textur->south
		|| !mlx->textur->north || !mlx->textur->west)
		error(LOAD_TEXTURES);
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
		ft_printf("Failed to create a new image\n");
		return ;
	}
	hook_mvt(mlx);
	cast_rays(mlx);
	mlx_image_to_window(mlx->mlx_ptr, mlx->imgage, 0, 0);
}

void	player_init(t_mlx *mlx, t_data *data, t_map *map)
{
	mlx->ply->player_x = (data->ply_y * TILE_SIZE) + (TILE_SIZE / 2);
	mlx->ply->player_y = (data->ply_x * TILE_SIZE) + (TILE_SIZE / 2);
	mlx->ply->fov = (FOV * M_PI) / 180;
	mlx->ply->ply_angle = M_PI;
	if (map->player == 'N')
		mlx->ply->ply_angle = 3 * M_PI / 2;
	else if (map->player == 'E')
		mlx->ply->ply_angle = 0;
	else if (map->player == 'W')
		mlx->ply->ply_angle = M_PI;
	else if (map->player == 'S')
		mlx->ply->ply_angle = M_PI / 2;
}
