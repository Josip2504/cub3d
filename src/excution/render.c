/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 05:12:44 by blatifat          #+#    #+#             */
/*   Updated: 2024/10/13 15:01:05 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

mlx_texture_t	*wall_texture(t_mlx *mlx, int flag)
{
	if (mlx->ray->angle < 0)
		mlx->ray->angle += 2 * WEST;
	else if (mlx->ray->angle > 2 * WEST)
		mlx->ray->angle -= 2 * WEST;
	if (flag == 0)
	{
		if (mlx->ray->angle > WEST / 2 && mlx->ray->angle < 3 * WEST / 2)
			return (mlx->textur->west);
		else
			return (mlx->textur->east);
	}
	else
	{
		if (mlx->ray->angle > 0 && mlx->ray->angle < WEST)
			return (mlx->textur->south);
		else
			return (mlx->textur->north);
	}
}

void	calculate_wall_texture_offsets(t_mlx *mlx,
	double wall_h, int t_pixel, t_texture_params *params)
{
	params->texture = wall_texture(mlx, mlx->ray->wall_flag);
	if (params->texture == NULL || params->texture->pixels == NULL)
		return ;
	params->scale_factor = (double)params->texture->height / wall_h;
	params->x_offset = get_x_offset(params->texture, mlx);
	params->y_offset = (t_pixel - (S_H / 2) + (wall_h / 2))
		* params->scale_factor;
	if (params->y_offset < 0)
		params->y_offset = 0.0;
}

void	draw_wall(t_mlx *mlx, int t_pixel, int b_pixel, double wall_h)
{
	t_texture_params	params;
	uint32_t			*arr;

	calculate_wall_texture_offsets(mlx, wall_h, t_pixel, &params);
	if (params.texture == NULL || params.texture->pixels == NULL)
		return ;
	arr = (uint32_t *)params.texture->pixels;
	while (t_pixel < b_pixel)
	{
		if ((uint32_t)params.y_offset >= params.texture->height)
			params.y_offset = params.texture->height - 1;
		if ((uint32_t)params.x_offset >= params.texture->width)
			params.x_offset = params.texture->width - 1;
		ft_put_pixel(mlx, mlx->ray->index, t_pixel,
			get_color(arr[(int)params.y_offset
				* params.texture->width + (int)params.x_offset]));
		params.y_offset += params.scale_factor;
		t_pixel++;
	}
}

void	draw_ceiling_floor(t_mlx *mlx, int ray, int t_pixel, int b_pixel)
{
	int		y;
	int		color;

	y = b_pixel;
	color = rgb_color(mlx->data->floor[0],
			mlx->data->floor[1], mlx->data->floor[2], 255);
	while (y < S_H)
		ft_put_pixel(mlx, ray, y++, color);
	color = rgb_color(mlx->data->ceil[0], mlx->data->ceil[1],
			mlx->data->ceil[2], 255);
	y = 0;
	while (y < t_pixel)
		ft_put_pixel(mlx, ray, y++, color);
}

void	render_wall_and_floor(t_mlx *mlx, int ray)
{
	double	wall_h;
	double	b_pixel;
	double	t_pixel;
	double	angle_diff;

	angle_diff = mlx->ray->angle - mlx->ply->ply_angle;
	if (angle_diff < 0)
		angle_diff += 2 * WEST;
	if (angle_diff > 2 * WEST)
		angle_diff -= 2 * WEST;
	mlx->ray->distance *= cos(angle_diff);
	wall_h = (TILE_SIZE / mlx->ray->distance)
		* ((S_W) / tan(mlx->ply->fov));
	b_pixel = (S_H / 2) + (wall_h / 2);
	t_pixel = (S_H / 2) - (wall_h / 2);
	if (b_pixel > S_H)
		b_pixel = S_H;
	if (t_pixel < 0)
		t_pixel = 0;
	mlx->ray->index = ray;
	draw_wall(mlx, t_pixel, b_pixel, wall_h);
	draw_ceiling_floor(mlx, ray, t_pixel, b_pixel);
}
