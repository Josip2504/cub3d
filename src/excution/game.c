/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 05:12:18 by blatifat          #+#    #+#             */
/*   Updated: 2024/09/07 05:49:18 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_mlx(t_mlx *mlx, t_game *game)
{
	mlx->mlx_ptr = mlx_init(S_W, S_H, "Cub3D", 0);
	if (!mlx->mlx_ptr)
	{
		printf("Erreur lors de l'initialisation de MLX\n");
		exit(EXIT_FAILURE);
	}
	mlx->image = mlx_new_image(mlx->mlx_ptr, S_W, S_H);
	if (!mlx->image)
	{
		printf("Erreur lors de la création de l'image\n");
		mlx_terminate(mlx->mlx_ptr);
		exit(EXIT_FAILURE);
	}
	mlx->game = game;
	mlx->player = game->player;
	mlx->ray = game->ray;
}

void	init_player(t_game *game, char orientation)
{
	game->player->player_x = (game->map->player_x * TILE_SIZE) + TILE_SIZE / 2;
	game->player->player_y = (game->map->player_y * TILE_SIZE) + TILE_SIZE / 2;

	game->player->fov = (FOV * M_PI / 180);

	if (orientation == 'N')
		game->player->angle = M_PI / 2;
	else if (orientation == 'S')
		game->player->angle = 3 * M_PI / 2;
	else if (orientation == 'E')
		game->player->angle = 0;
	else if (orientation == 'W')
		game->player->angle = M_PI;
}

void	mlx_image_clear(mlx_image_t *image, uint32_t color)
{
	size_t	pixel_count;

	pixel_count = image->width * image->height;
	ft_memset(image->pixels, color, pixel_count * sizeof(uint32_t));
}

/* void handle_keypress(mlx_key_data_t keydata, void *param)
{
    t_game *game = (t_game *)param;
    input_handler(game, keydata); // Call input_handler when key is pressed
}
 */

void	game_loop(void *param)
{
	t_game			*game;
	/* mlx_key_data_t	keydata; */
	t_mlx			mlx_data;

	game = (t_game *)param;
	mlx_image_clear(game->image, 0x00000000);
	/* input_handler(game, keydata); */
	rays_cast(game, &mlx_data);
	mlx_image_to_window(game->mlx, game->image, 0, 0);
}


/* void	init_player(t_game *game)
{
	// Place le joueur au centre d'une tuile
	game->player->player_x = (game->map->player_x * TILE_SIZE) + TILE_SIZE / 2;
	game->player->player_y = (game->map->player_y * TILE_SIZE) + TILE_SIZE / 2;
	game->player->angle = M_PI;  // Le joueur regarde vers l'ouest au départ
	game->player->fov = FOV * (M_PI / 180);  // Convertir le FOV en radians
	game->player->rotation = 0;
	game->player->left_right = 0;
	game->player->up_down = 0;
}

void	init_game(t_game *game, t_map *map)
{
	// Alloue la mémoire pour les structures
	game->player = malloc(sizeof(t_player));
	game->ray = malloc(sizeof(t_ray));
	game->map = map;

	// Initialise le joueur et ses paramètres
	init_player(game);

	// Charge les textures
	load_textures(game);
} */