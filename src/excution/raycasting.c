/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 05:11:38 by blatifat          #+#    #+#             */
/*   Updated: 2024/09/07 05:45:31 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	find_wall_hit(double ray_angle, t_game *game, t_ray *ray, int ray_id)
{
	double	distance_h;
	double	distance_v;

	(void)ray_id;
	distance_h = find_h_intersection(ray_angle, game);
	distance_v = find_v_intersection(ray_angle, game);
	if (distance_h < distance_v)
	{
		ray->distance = distance_h;
		ray->wall_flag = 1;
	}
	else
	{
		ray->distance = distance_v;
		ray->wall_flag = 0;
	}
}

double	normaliz_angle(double angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

void	rays_cast(t_game *game, t_mlx *mlx)
{
	int		ray;
	int		rays_num;
	double	ray_angle;
	double	angle_step;
	double	corrected_distance;

	ray = 0;
	rays_num = S_W;
	angle_step = game->player->fov / rays_num;
	while (ray < rays_num)
	{
		ray_angle = (game->player->angle
				- (game->player->fov / 2) + ray * angle_step);
		ray_angle = normaliz_angle(ray_angle);
		printf("Ray %d: angle = %f radians\n", ray, ray_angle);
		find_wall_hit(ray_angle, game, mlx->ray, ray);
		corrected_distance = mlx->ray->distance
			* cos(ray_angle - game->player->angle);
		/* render_wall(mlx, ray, mlx->ray->distance); */
		render_wall(game, mlx, ray);
		ray++;
	}
}
