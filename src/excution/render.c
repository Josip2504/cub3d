/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 05:12:44 by blatifat          #+#    #+#             */
/*   Updated: 2024/09/23 17:00:18 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
// {
// 	if (x >= 0 && x < S_W && y >= 0 && y < S_H)
// 		mlx_put_pixel(mlx->imgage, x, y, color);
// }

// void	draw_ceiling_floor(t_mlx *mlx, int ray, int t_pix, int b_pix)
// {
// 	int	y;

// 	y = 0;
// 	while (y < t_pix)
// 	{
// 		my_mlx_pixel_put(mlx, ray, y, 0x98FF98FF);
// 		y++;
// 	}
// 	y = b_pix;
// 	while (y < S_H)
// 	{
// 		my_mlx_pixel_put(mlx, ray, y, 0xFFFFE0FF);
// 		y++;
// 	}
// }

// int	get_wall_color(t_mlx *mlx)
// {
// 	double	angle;

// 	angle = mlx->ray->angle;
// 	if (angle < 0)
// 		angle += (2 * M_PI);
// 	else if (angle > 2 * M_PI)
// 		angle -= (2 * M_PI);
// 	if (mlx->ray->wall_flag == 0)
// 	{
// 		if (angle > M_PI / 2 && angle < 3 * M_PI / 2)
// 			return (0xFF7F50FF);
// 		return (0xFF7F50FF);
// 	}
// 	else
// 	{
// 		if (angle > 0 && angle < M_PI)
// 			return (0xE6E6FAFF);
// 		return (0xE6E6FAFF);
// 	}
// }

// void	draw_wall(t_mlx *mlx, int ray,
// 	int t_pix, int b_pix)
// {
// 	int	color;

// 	color = get_wall_color(mlx);
// 	while (t_pix < b_pix)
// 	{
// 		my_mlx_pixel_put(mlx, ray, t_pix, color);
// 		t_pix++;
// 	}
// }

// void	render_wall_and_floor(t_mlx *mlx, int ray)
// {
// 	double	wall_h;
// 	double	b_pix;
// 	double	t_pix;

// 	mlx->ray->distance *= cos(mlx->ray->angle - mlx->ply->angle);
// 	wall_h = (TILE_SIZE / mlx->ray->distance)
// 		* ((S_W / 2) / tan(mlx->ply->fov / 2));
// 	t_pix = (S_H / 2) - (wall_h / 2);
// 	b_pix = (S_H / 2) + (wall_h / 2);
// 	if (t_pix < 0)
// 		t_pix = 0;
// 	if (b_pix > S_H)
// 		b_pix = S_H;
// 	draw_wall(mlx, ray, t_pix, b_pix);
// 	draw_ceiling_floor(mlx, ray, t_pix, b_pix);
// }


		// new for texture


 unsigned int reverse_bytes(unsigned int num)
{
    unsigned int reversed = 0;

    // Shift and mask each byte, then place it in the reversed position
    reversed |= (num & 0x000000FF) << 24;  // Move byte 0 to byte 3
    reversed |= (num & 0x0000FF00) << 8;   // Move byte 1 to byte 2
    reversed |= (num & 0x00FF0000) >> 8;   // Move byte 2 to byte 1
    reversed |= (num & 0xFF000000) >> 24;  // Move byte 3 to byte 0

    return reversed;
}

float	nor_angle(float angle)
{
	if (angle < 0)
		angle += 2 * M_PI;
	else if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

// Convert RGBA values to a 32-bit integer
uint32_t	rgb_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

// Reverse the bytes of a color
unsigned int	get_color(int c)
{
	return (((c & 0x000000FF) << 24) | ((c & 0x0000FF00) << 8)
		| ((c & 0x00FF0000) >> 8) | ((c & 0xFF000000) >> 24));
}


// Draw a pixel if it's within screen bounds
void	ft_put_pixel(t_mlx *mlx, int x, int y, int color)
{
	if (x >= 0 && x < S_W && y >= 0 && y < S_H)
		mlx_put_pixel(mlx->imgage, x, y, color);
}

// Choose the appropriate texture based on the ray angle
mlx_texture_t *wall_texture(t_mlx *mlx, int flag)
{
	mlx->ray->angle = nor_angle(mlx->ray->angle);
	if (flag == 0)
	{
		if (mlx->ray->angle > M_PI / 2 && mlx->ray->angle < 3 * M_PI / 2)
			return (mlx->textur->west);  // West wall texture
		else
			return (mlx->textur->east);  // East wall texture
	}
	else
	{
		if (mlx->ray->angle > 0 && mlx->ray->angle < M_PI)
			return (mlx->textur->south);  // South wall texture
		else
			return (mlx->textur->north);  // North wall texture
	}
}

// Draw ceiling and floor based on texture or color data
void	draw_ceiling_floor(t_mlx *mlx, int ray, int t_pix, int b_pix)
{
	int		y;
	int		color;

	// Draw floor
	color = rgb_color(mlx->data->floor[0], mlx->data->floor[1], mlx->data->floor[2], 255);
	y = b_pix;
	while (y < S_H)
		ft_put_pixel(mlx, ray, y++, color);

	// Draw ceiling
	color = rgb_color(mlx->data->ceil[0], mlx->data->ceil[1], mlx->data->ceil[2], 255);
	y = 0;
	while (y < t_pix)
		ft_put_pixel(mlx, ray, y++, color);
}

// Calculate x_offset based on the texture and wall hit position
double	get_x_offset(mlx_texture_t *texture, t_mlx *mlx)
{
	double	x_o;
	double	wall_hit;

	if (mlx->ray->wall_flag == 1)  // If vertical hit
	{
		wall_hit = mlx->ply->player_x + (mlx->ray->distance * cos(mlx->ray->angle));
		x_o = fmod(wall_hit, TILE_SIZE) / TILE_SIZE * texture->width;
	}
	else  // Horizontal hit
	{
		wall_hit = mlx->ply->player_y + (mlx->ray->distance * sin(mlx->ray->angle));
		x_o = fmod(wall_hit, TILE_SIZE) / TILE_SIZE * texture->width;
	}
	return (x_o);
}

// Draw the wall by calculating x and y offsets
void	draw_wall(t_mlx *mlx, int t_pix, int b_pix, double wall_h)
{
	double			x_o;
	double			y_o;
	double			factor;
	uint32_t		*arr;
	mlx_texture_t	*texture = NULL;

	texture = wall_texture(mlx, mlx->ray->wall_flag);
	arr = (uint32_t *)texture->pixels;
	factor = (double)texture->height / wall_h;
	x_o = get_x_offset(texture, mlx);
	y_o = (t_pix - (S_H / 2) + (wall_h / 2)) * factor;
	if (y_o < 0)
		y_o = 0;
	while (t_pix < b_pix)
	{
		ft_put_pixel(mlx, mlx->ray->index, t_pix, reverse_bytes(arr[(int)y_o * texture->width + (int)x_o]));
		y_o += factor;
		t_pix++;
	}
}
// Render the wall and floor/ceiling
void	render_wall_and_floor(t_mlx *mlx, int ray)
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

	mlx->ray->distance *= cos(mlx->ray->angle - mlx->ply->angle);
	wall_h = (TILE_SIZE / mlx->ray->distance) * ((S_W / 2) / tan(mlx->ply->fov));
	b_pix = (S_H / 2) + (wall_h / 2);
	t_pix = (S_H / 2) - (wall_h / 2);
	if (b_pix > S_H)
		b_pix = S_H;
	if (t_pix < 0)
		t_pix = 0;
	mlx->ray->index = ray;
	draw_wall(mlx, t_pix, b_pix, wall_h);
	draw_ceiling_floor(mlx, ray, t_pix, b_pix);
}
