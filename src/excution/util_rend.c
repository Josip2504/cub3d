/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_rend.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 01:03:15 by blatifat          #+#    #+#             */
/*   Updated: 2024/10/04 01:13:36 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

double	get_x_offset(mlx_texture_t *texture, t_mlx *mlx)
{
	double	x_o;
	double	wall_hit;

	if (mlx->ray->wall_flag == 1)
	{
		wall_hit = mlx->ply->player_x
			+ (mlx->ray->distance * cos(mlx->ray->angle));
		x_o = fmod(wall_hit + 0.0001, TILE_SIZE) / TILE_SIZE * texture->width;
	}
	else
	{
		wall_hit = mlx->ply->player_y
			+ (mlx->ray->distance * sin(mlx->ray->angle));
		x_o = fmod(wall_hit + 0.0001, TILE_SIZE) / TILE_SIZE * texture->width;
	}
	return (x_o);
}

uint32_t	rgb_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a << 0);
}

unsigned int	get_color(int c)
{
	return (((c & 0x000000FF) << 24) | ((c & 0x0000FF00) << 8)
		| ((c & 0x00FF0000) >> 8) | ((c & 0xFF000000) >> 24));
}

void	ft_put_pixel(t_mlx *mlx, int x, int y, int color)
{
	if (x >= 0 && x < S_W && y >= 0 && y < S_H)
		mlx_put_pixel(mlx->imgage, x, y, color);
}
