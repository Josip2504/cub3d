/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayon.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 23:56:19 by blatifat          #+#    #+#             */
/*   Updated: 2024/09/06 20:34:23 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	wall_hit(double x, double y, t_game *game)
{
	int	map_x;
	int	map_y;

	map_x = floor(x / TILE_SIZE);
	map_y = floor(y / TILE_SIZE);
	if (map_x < 0 || map_x >= game->map->map_width
		|| map_y < 0 || map_y >= game->map->map_height)
		return (1);
	if (game->map->map2d[map_y][map_x] == '1')
		return (1);
	return (0);
}

double	find_v_intersection(double ray_angle, t_game *game)
{
	double	x_step;
	double	y_step;
	double	x_hit;
	double	y_hit;

	x_hit = floor(game->player->player_x / TILE_SIZE) * TILE_SIZE;
	if (ray_angle < M_PI_2 || ray_angle > 3 * M_PI_2)
		x_hit += TILE_SIZE;
	else
		x_hit -= 1;
	y_hit = game->player->player_y
		+ (x_hit - game->player->player_x) * tan(ray_angle);
	if (ray_angle < M_PI_2 || ray_angle > 3 * M_PI_2)
		x_step = TILE_SIZE;
	else
		x_step = -TILE_SIZE;
	y_step = TILE_SIZE * tan(ray_angle);
	while (!wall_hit(x_hit, y_hit, game))
	{
		x_hit += x_step;
		y_hit += y_step;
	}
	return (sqrt(pow(x_hit - game->player->player_x, 2)
			+ pow(y_hit - game->player->player_y, 2)));
}

double	find_h_intersection(double ray_angle, t_game *game)
{
	double	x_step;
	double	y_step;
	double	x_hit;
	double	y_hit;

	y_hit = floor(game->player->player_y / TILE_SIZE) * TILE_SIZE;
	if (ray_angle > 0 && ray_angle < M_PI)
		y_hit += TILE_SIZE;
	else
		y_hit -= 1;
	x_hit = game->player->player_x
		+ (y_hit - game->player->player_y) / tan(ray_angle);
	if (ray_angle > 0 && ray_angle < M_PI)
		y_step = TILE_SIZE;
	else
		y_step = -TILE_SIZE;
	x_step = TILE_SIZE / tan(ray_angle);

	while (!wall_hit(x_hit, y_hit, game))
	{
		x_hit += x_step;
		y_hit += y_step;
	}
	return (sqrt(pow(x_hit - game->player->player_x, 2)
			+ pow(y_hit - game->player->player_y, 2)));
}

