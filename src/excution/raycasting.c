/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 05:11:38 by blatifat          #+#    #+#             */
/*   Updated: 2024/10/16 13:46:31 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	wall_hit(float x, float y, t_mlx *mlx)
{
	int		x_m;
	int		y_m;
	char	*current_row;

	if (x < 0 || y < 0)
		return (0);
	x_m = (int)(x / TILE_SIZE);
	y_m = (int)(y / TILE_SIZE);
	if (y_m >= mlx->data->height_map || x_m >= mlx->data->width_map)
		return (0);
	current_row = mlx->data->map2d[y_m];
	if (current_row && x_m < (int)ft_strlen(current_row))
		return (current_row[x_m] != '1');
	return (1);
}

float	ver_intersection(t_mlx *mlx, float angle)
{
	int		pixel;
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;

	x_step = TILE_SIZE;
	y_step = TILE_SIZE * tan(angle);
	v_x = (int)(mlx->ply->player_x / TILE_SIZE) * TILE_SIZE - 0.1; 			// -0.1
	pixel = evaluate_intersection(angle, &v_x, &x_step, 0);
	v_y = mlx->ply->player_y + (v_x - mlx->ply->player_x) * tan(angle) + 0.1;
	if ((verify_circle(angle, 'x') && y_step < 0)
		|| (!verify_circle(angle, 'x') && y_step > 0))
		y_step = -y_step;
	while (wall_hit(v_x - pixel, v_y, mlx))
	{
		v_x += x_step;
		v_y += y_step;
	}
	mlx->ray->hor_x = v_x;
	mlx->ray->hor_y = v_y;
	return (sqrt(pow(v_x - mlx->ply->player_x, 2)
			+ pow(v_y - mlx->ply->player_y, 2)));
}

float	hor_intersection(t_mlx *mlx, float angle)
{
	int		pixel;
	float	h_x;
	float	h_y;
	float	x_step;
	float	y_step;

	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angle);
	h_y = floor(mlx->ply->player_y / TILE_SIZE) * TILE_SIZE - 0.1;			// -0.1
	pixel = evaluate_intersection(angle, &h_y, &y_step, 1);
	h_x = mlx->ply->player_x + (h_y - mlx->ply->player_y) / tan(angle) + 0.1;
	if ((verify_circle(angle, 'y') && x_step > 0) || \
		(!verify_circle(angle, 'y') && x_step < 0))
		x_step *= -1;
	while (wall_hit(h_x, h_y - pixel, mlx))
	{
		h_x += x_step;
		h_y += y_step;
	}
	mlx->ray->hor_x = h_x;
	mlx->ray->hor_y = h_y;
	return (sqrt(pow(h_x - mlx->ply->player_x, 2)
			+ pow(h_y - mlx->ply->player_y, 2)));
}

void	calculate_ray_intersections(t_mlx *mlx, int ray)
{
	double	v_inter;
	double	h_inter;
	double	two_pi;

	two_pi = 2 * M_PI;
	if (mlx->ray->angle < 0)
		mlx->ray->angle += two_pi;
	if (mlx->ray->angle > two_pi)
		mlx->ray->angle -= two_pi;
	h_inter = hor_intersection(mlx, mlx->ray->angle);
	v_inter = ver_intersection(mlx, mlx->ray->angle);
	if (v_inter <= h_inter)
	{
		mlx->ray->distance = v_inter;
		mlx->ray->wall_flag = 0;
	}
	else
	{
		mlx->ray->distance = h_inter;
		mlx->ray->wall_flag = 1;
	}
	render_wall_and_floor(mlx, ray);
}

void	cast_rays(t_mlx *mlx)
{
	int		ray;
	double	initial_angle;
	double	angle_increment;

	ray = 0;
	initial_angle = mlx->ply->ply_angle - (mlx->ply->fov / 2);
	angle_increment = mlx->ply->fov / S_W;
	while (ray <= S_W)
	{
		mlx->ray->angle = initial_angle + ray * angle_increment;
		calculate_ray_intersections(mlx, ray);
		ray++;
	}
}
