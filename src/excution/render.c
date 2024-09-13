/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 05:12:44 by blatifat          #+#    #+#             */
/*   Updated: 2024/09/13 12:23:22 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	if (x >= 0 && x < S_W && y >= 0 && y < S_H)
		mlx_put_pixel(mlx->imgage, x, y, color);
}

void	draw_ceiling_floor(t_mlx *mlx, int ray, int t_pix, int b_pix)
{
	int	y;

	y = 0;
	while (y < t_pix)
	{
		my_mlx_pixel_put(mlx, ray, y, 0x98FF98FF);
		y++;
	}
	y = b_pix;
	while (y < S_H)
	{
		my_mlx_pixel_put(mlx, ray, y, 0xFFFFE0FF);
		y++;
	}
}

int	get_wall_color(t_mlx *mlx)
{
	double	angle;

	angle = mlx->ray->angle;
	if (angle < 0)
		angle += (2 * M_PI);
	else if (angle > 2 * M_PI)
		angle -= (2 * M_PI);
	if (mlx->ray->wall_flag == 0)
	{
		if (angle > M_PI / 2 && angle < 3 * M_PI / 2)
			return (0xFF7F50FF);
		return (0xFF7F50FF);
	}
	else
	{
		if (angle > 0 && angle < M_PI)
			return (0xE6E6FAFF);
		return (0xE6E6FAFF);
	}
}

void	draw_wall(t_mlx *mlx, int ray,
	int t_pix, int b_pix)
{
	int	color;

	color = get_wall_color(mlx);
	while (t_pix < b_pix)
	{
		my_mlx_pixel_put(mlx, ray, t_pix, color);
		t_pix++;
	}
}

void	render_wall_and_floor(t_mlx *mlx, int ray)
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

	mlx->ray->distance *= cos(mlx->ray->angle - mlx->ply->angle);
	wall_h = (TILE_SIZE / mlx->ray->distance)
		* ((S_W / 2) / tan(mlx->ply->fov / 2));
	t_pix = (S_H / 2) - (wall_h / 2);
	b_pix = (S_H / 2) + (wall_h / 2);
	if (t_pix < 0)
		t_pix = 0;
	if (b_pix > S_H)
		b_pix = S_H;
	draw_wall(mlx, ray, t_pix, b_pix);
	draw_ceiling_floor(mlx, ray, t_pix, b_pix);
}
