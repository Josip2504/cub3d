/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 05:12:44 by blatifat          #+#    #+#             */
/*   Updated: 2024/09/07 05:46:30 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

double	get_x_offset(mlx_texture_t *texture, t_game *game)
{
	double	x_wall;

	if (game->ray->wall_flag == 0)
		x_wall = fmod(game->player->player_x / TILE_SIZE, 1.0) * texture->width;
	else
		x_wall = fmod(game->player->player_x / TILE_SIZE, 1.0) * texture->width;
	return (x_wall);
}

uint32_t	rgb_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_ceilling_floor(t_game *game, int ray,
	int wall_top, int wall_bottom)
{
	int			y;
	uint32_t	ceiling_color;
	uint32_t	floor_color;
	t_mlx		*mlx;

	y = 0;
	mlx = NULL;
	ceiling_color = rgb_color(game->map->ceiling[0],
			game->map->ceiling[1], game->map->ceiling[2], 255);
	floor_color = rgb_color(game->map->floor[0],
			game->map->floor[1], game->map->floor[2], 255);
	while (y < wall_top)
	{
		mlx_put_pixel(mlx->image, ray, y, ceiling_color);
		y++;
	}
	y = wall_bottom;
	while (y < S_H)
	{
		mlx_put_pixel(mlx->image, ray, y, floor_color);
		y++;
	}
}

void	draw_wall(t_game *game, t_mlx *mlx, t_wall_params params)
{
	double			y_offset;
	double			x_offset;
	double			textur_factor;
	uint32_t		*texture_pixel;
	mlx_texture_t	*texture;

	texture = wall_texture(game, game->ray->wall_flag);
	texture_pixel = (uint32_t *)texture->pixels;
	textur_factor = texture->height / params.wall_height;
	x_offset = get_x_offset(texture, game);
	y_offset = (params.top_pixel - (S_H / 2)
			+ (params.wall_height / 2)) * textur_factor;
	if (y_offset < 0)
		y_offset = 0.0;
	while (params.top_pixel < params.bottom_pixel)
	{
		mlx_put_pixel(mlx->image, params.ray, params.top_pixel,
			texture_pixel[(int)y_offset * texture->width + (int)x_offset]);
		y_offset += textur_factor;
		params.top_pixel++;
	}
}

void	render_wall(t_game *game, t_mlx *mlx, int ray)
{
	double			wall_height;
	double			wall_top;
	double			wall_bottom;
	t_wall_params	params;

	game->ray->distance *= cos(game->ray->ray_angel - game->player->angle);
	wall_height = (TILE_SIZE / game->ray->distance)
		* (S_W / 2) / tan(game->player->fov / 2);
	wall_top = (S_H / 2) - (wall_height / 2);
	wall_bottom = (S_H / 2) + (wall_height / 2);

	if (wall_top < 0) 
		wall_top = 0;
	if (wall_bottom >= S_H)
		wall_bottom = S_H - 1;
	params.wall_height = wall_height;
	params.top_pixel = wall_top;
	params.bottom_pixel = wall_bottom;
	params.ray = ray;
	draw_wall(game, mlx, params);
	draw_ceilling_floor(game, ray, wall_top, wall_bottom);
}
