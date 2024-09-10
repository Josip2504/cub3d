/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 05:58:37 by blatifat          #+#    #+#             */
/*   Updated: 2024/09/07 06:40:41 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	hooks_setup(t_game *game)
{
	mlx_key_hook(game->mlx, input_handler, game);
	mlx_loop_hook(game->mlx, game_loop, game);
}

void	close_window(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	free_game_resources(game);
	exit(0);
}

void	setup_hooks(t_game *game)
{
	mlx_key_hook(game->mlx, input_handler, game);
	mlx_loop_hook(game->mlx, game_loop, game);
    mlx_close_hook(game->mlx, &close_window, game);
}


void start_game(t_game *game, char orientation)
{
    // Initialiser MiniLibX
    game->mlx = mlx_init(S_W, S_H, "Cub3D", 0);
    if (!game->mlx) {
        printf("Erreur lors de l'initialisation de MLX\n");
        exit(1);
    }

    // Créer une nouvelle image
    game->image = mlx_new_image(game->mlx, S_W, S_H);
    if (!game->image) {
        printf("Erreur lors de la création de l'image\n");
        exit(1);
    }

    // Charger les textures (pour les murs et autres éléments)
    laod_textures(game);

    // Initialiser le joueur (position, angle)
    init_player(game, orientation);

    // Configurer les hooks pour gérer les événements clavier et fenêtre
    setup_hooks(game);

    // Lancer la boucle principale de MLX (ce qui fait tourner le jeu)
    mlx_loop(game->mlx);
    
    // Libérer les ressources quand le jeu est terminé
    free_game_resources(game);
}
