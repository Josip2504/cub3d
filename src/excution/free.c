/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:04:44 by blatifat          #+#    #+#             */
/*   Updated: 2024/09/07 07:22:28 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
/* 

void free_textures(t_game *game)
{
    // Libère chaque texture si elle est chargée
    if (game->up)
        mlx_delete_texture(game->up);  // Correctement libérer la texture
    if (game->down)
        mlx_delete_texture(game->down);
    if (game->left)
        mlx_delete_texture(game->left);
    if (game->right)
        mlx_delete_texture(game->right);
}


void free_map(t_map *map)
{
    int i = 0;

    if (map->map2d)
    {
        while (i < map->map_height)
        {
            free(map->map2d[i]);  // Libère chaque ligne de la carte
            i++;
        }
        free(map->map2d);  // Libère le tableau de lignes
    }
    free(map);  // Libère la structure de la carte elle-même
}


void	free_mlx_struct(t_mlx *mlx)
{
	if (mlx->image)
		mlx_delete_image(mlx->mlx_ptr, mlx->image);
	if (mlx->mlx_ptr)
		mlx_terminate(mlx->mlx_ptr);
}

 */

void free_map(t_map *map)
{
    int i = 0;

    if (map->map2d)
    {
        while (i < map->map_height)
        {
            free(map->map2d[i]);  // Libère chaque ligne de la carte
            i++;
        }
        free(map->map2d);  // Libère le tableau de lignes
    }
    free(map);  // Libère la structure de la carte elle-même
}


void free_game_resources(t_game *game) {
    if (game->image)
        mlx_delete_image(game->mlx, game->image);
    
    if (game->up)
        mlx_delete_texture(game->up);
    if (game->down)
        mlx_delete_texture(game->down);
    if (game->left)
        mlx_delete_texture(game->left);
    if (game->right)
        mlx_delete_texture(game->right);

    // Libération du joueur et de la carte
    if (game->player)
        free(game->player);
    if (game->map)
        free_map(game->map);  // Assurez-vous d'avoir une fonction free_map().

    // Terminer MLX
    mlx_terminate(game->mlx);
}
