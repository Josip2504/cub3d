/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 05:11:38 by blatifat          #+#    #+#             */
/*   Updated: 2024/10/04 19:20:05 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* int	wall_hit(float x, float y, t_mlx *mlx)
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
		if (x_m < (int)ft_strlen(mlx->data->map2d[y_m]))
		{
			if (mlx->data->map2d[y_m][x_m] == '1')
				return (0);
		}
	}
	return (1);
}

float	hor_intersection(t_mlx *mlx, float angl)
{
	float	h_x = 0.0;
	float	h_y = 0.0;
	float	x_step = 0.0;
	float	y_step = 0.0;
	int		pixel = 0;

	angl = nor_angle(angl);
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
			+ pow(h_y - mlx->ply->player_y, 2)) + 0.1000);
}

float	ver_intersection(t_mlx *mlx, float angl)
{
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int		pixel;

	angl = nor_angle(angl);
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

void	calculate_ray_intersections(t_mlx *mlx)
{
	double	h_inter = 0.0;
	double	v_inter = 0.0;

	// if (mlx->ray->angle < 0)
	// 	mlx->ray->angle += (2 * M_PI);
	// else if (mlx->ray->angle > (2 * M_PI))
	// 	mlx->ray->angle -= (2 * M_PI);
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
	mlx->ray->angle = mlx->ply->ply_angle - (mlx->ply->fov / 2);
	while (ray <= S_W)
	{
		calculate_ray_intersections(mlx);
		render_wall_and_floor(mlx, ray);
		ray++;
		mlx->ray->angle += (mlx->ply->fov / S_W);
	}
}
 */

/* int verify_circle(float angle, char c)
{
    if (c == 'x')
    {
        if (angle > 0 && angle < M_PI)  // Demi-cercle supérieur
            return (1);
    }
    else if (c == 'y')
    {
        if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)  // Demi-cercle gauche
            return (1);
    }
    return (0);
} */

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
	v_x = (int)(mlx->ply->player_x / TILE_SIZE) * TILE_SIZE;
	pixel = evaluate_intersection(angle, &v_x, &x_step, 0);
	v_y = mlx->ply->player_y + (v_x - mlx->ply->player_x) * tan(angle);
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
	h_y = floor(mlx->ply->player_y / TILE_SIZE) * TILE_SIZE;
	pixel = evaluate_intersection(angle, &h_y, &y_step, 1);
	h_x = mlx->ply->player_x + (h_y - mlx->ply->player_y) / tan(angle);
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
			+ pow(h_y - mlx->ply->player_y, 2)) + 0.0001);
}

void	calculate_ray_intersections(t_mlx *mlx, int ray)
{
	double	v_inter;
	double	h_inter;

	if (mlx->ray->angle < 0)
		mlx->ray->angle += 2 * M_PI;
	if (mlx->ray->angle > 2 * M_PI)
		mlx->ray->angle -= 2 * M_PI;
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
