/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 05:11:38 by blatifat          #+#    #+#             */
/*   Updated: 2024/09/23 16:59:52 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	wall_hit(float x, float y, t_mlx *mlx)
{
	int	x_m;
	int	y_m;

	if (x < 0 || y < 0)
		return (0);

	x_m = floor(x / TILE_SIZE);
	y_m = floor(y / TILE_SIZE);
	if (y_m >= mlx->data->height_map || x_m >= mlx->data->width_map)
		return (0);
	if (mlx->data->map2d[y_m] != NULL)
	{
		if (x_m < (int)strlen(mlx->data->map2d[y_m]))
		{
			if (mlx->data->map2d[y_m][x_m] == '1')
				return (0);
		}
	}
	return (1);
}

float	hor_intersection(t_mlx *mlx, float angl)
{
	float	h_x;
	float	h_y;
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angl);
	h_y = floor(mlx->ply->player_y / TILE_SIZE) * TILE_SIZE;
	pixel = intersection_checking(angl, &h_y, &y_step, 1);
	h_x = mlx->ply->player_x + (h_y - mlx->ply->player_y) / tan(angl);

	if (get_unit_circle(angl, 'y'))
	{
		if (x_step > 0)
			x_step = -x_step;
	}
	while (wall_hit(h_x, h_y - pixel, mlx))
	{
		h_x += x_step;
		h_y += y_step;
	}
	return (sqrt(pow(h_x - mlx->ply->player_x, 2)
			+ pow(h_y - mlx->ply->player_y, 2)));
}

float	ver_intersection(t_mlx *mlx, float angl)
{
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = TILE_SIZE;
	y_step = TILE_SIZE * tan(angl);
	v_x = floor(mlx->ply->player_x / TILE_SIZE) * TILE_SIZE;
	pixel = intersection_checking(angl, &v_x, &x_step, 0);
	v_y = mlx->ply->player_y + (v_x - mlx->ply->player_x) * tan(angl);
	if (get_unit_circle(angl, 'x'))
	{
		if (y_step < 0)
			y_step = -y_step;
	}
	while (wall_hit(v_x - pixel, v_y, mlx))
	{
		v_x += x_step;
		v_y += y_step;
	}
	return (sqrt(pow(v_x - mlx->ply->player_x, 2)
			+ pow(v_y - mlx->ply->player_y, 2)));
}

void	calculate_ray_intersections(t_mlx *mlx, int ray)
{
	double	h_inter;
	double	v_inter;

	(void)ray;
	if (mlx->ray->angle < 0)
		mlx->ray->angle += (2 * M_PI);
	else if (mlx->ray->angle > (2 * M_PI))
		mlx->ray->angle -= (2 * M_PI);
	mlx->ray->wall_flag = 0;
	h_inter = hor_intersection(mlx, mlx->ray->angle);
	v_inter = ver_intersection(mlx, mlx->ray->angle);
	if (v_inter <= h_inter)
		mlx->ray->distance = v_inter;
	else
	{
		mlx->ray->distance = h_inter;
		mlx->ray->wall_flag = 1;
	}
}

void	cast_rays(t_mlx *mlx)
{
	int	ray;

	ray = 0;
	mlx->ray->angle = mlx->ply->angle - (mlx->ply->fov / 2);

	while (ray < S_W)
	{
		calculate_ray_intersections(mlx, ray);
		render_wall_and_floor(mlx, ray);
		ray++;
		mlx->ray->angle += (mlx->ply->fov / S_W);
	}
}

