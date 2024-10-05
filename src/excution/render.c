/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 05:12:44 by blatifat          #+#    #+#             */
/*   Updated: 2024/10/04 20:30:12 by jsamardz         ###   ########.fr       */
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


/* unsigned int	reverse_bytes(unsigned int num)
{
	unsigned int	reversed;

	reversed = 0;
    // Shift and mask each byte, then place it in the reversed position
    reversed |= (num & 0x000000FF) << 24;  // Move byte 0 to byte 3
    reversed |= (num & 0x0000FF00) << 8;   // Move byte 1 to byte 2
    reversed |= (num & 0x00FF0000) >> 8;   // Move byte 2 to byte 1
    reversed |= (num & 0xFF000000) >> 24;  // Move byte 3 to byte 0
    return reversed;
} */

/* float	nor_angle(float angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
} */

mlx_texture_t	*wall_texture(t_mlx *mlx, int flag)
{
	if (mlx->ray->angle < 0)
		mlx->ray->angle += 2 * M_PI;
	else if (mlx->ray->angle > 2 * M_PI)
		mlx->ray->angle -= 2 * M_PI;
	if (flag == 0)
	{
		if (mlx->ray->angle > M_PI / 2 && mlx->ray->angle < 3 * M_PI / 2)
			return (mlx->textur->west);
		else
			return (mlx->textur->east);
	}
	else
	{
		if (mlx->ray->angle > 0 && mlx->ray->angle < M_PI)
			return (mlx->textur->south);
		else
			return (mlx->textur->north);
	}
}

void calculate_wall_texture_offsets(t_mlx *mlx, double wall_h, int t_pixel, t_texture_params *params)
{
    params->texture = wall_texture(mlx, mlx->ray->wall_flag);
    if (params->texture == NULL || params->texture->pixels == NULL)
        return ;
    params->scale_factor = (double)params->texture->height / wall_h;
    params->x_offset = get_x_offset(params->texture, mlx);
    params->y_offset = (t_pixel - (S_H / 2) + (wall_h / 2)) * params->scale_factor;
    if (params->y_offset < 0)
        params->y_offset = 0.0;
}

void draw_wall(t_mlx *mlx, int t_pixel, int b_pixel, double wall_h)
{
    t_texture_params params;
    uint32_t *arr;

    // Calculer les offsets de la texture (x_offset, y_offset, etc.)
    calculate_wall_texture_offsets(mlx, wall_h, t_pixel, &params);

    // Si la texture n'est pas valide, on quitte la fonction
    if (params.texture == NULL || params.texture->pixels == NULL)
        return;

    // Récupérer les pixels de la texture
    arr = (uint32_t *)params.texture->pixels;

    // Boucle pour dessiner chaque pixel vertical du mur
    while (t_pixel < b_pixel)
    {
        // S'assurer que les offsets sont dans les limites de la texture
        if ((uint32_t)params.y_offset >= params.texture->height)
            params.y_offset = params.texture->height - 1;
        if ((uint32_t)params.x_offset >= params.texture->width)
            params.x_offset = params.texture->width - 1;

        // Dessiner le pixel avec la couleur correspondante
        ft_put_pixel(mlx, mlx->ray->index, t_pixel, get_color(arr[(int)params.y_offset * params.texture->width + (int)params.x_offset]));

        // Passer au pixel suivant en ajustant l'offset y
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


/* void	draw_wall(t_mlx *mlx, int t_pixel, int b_pixel, double wall_h)
{
	double			x_o;
	double			y_o;
	double			factor;
	uint32_t		*arr;
	mlx_texture_t	*texture;

	texture = wall_texture(mlx, mlx->ray->wall_flag);
	texture = wall_texture(mlx, mlx->ray->wall_flag);
	if (texture == NULL || texture->pixels == NULL)
		return ;
	arr = (uint32_t *)texture->pixels;
	factor = (double)texture->height / wall_h;
	x_o = get_x_offset(texture, mlx);
	y_o = (t_pixel - (S_H / 2) + (wall_h / 2)) * factor;
	if (y_o < 0)
		y_o = 0.0;
	while (t_pixel < b_pixel)
	{
		if ((uint32_t)y_o >= texture->height)
			y_o = texture->height - 1;
		if ((uint32_t)x_o >= texture->width)
			x_o = texture->width - 1;
		ft_put_pixel(mlx, mlx->ray->index, t_pixel,
			get_color(arr[(int)y_o * texture->width + (int)x_o]));
		y_o += factor;
		t_pixel++;
	}
} */

void	render_wall_and_floor(t_mlx *mlx, int ray)
{
	double	wall_h;
	double	b_pixel;
	double	t_pixel;
	double	angle_diff;

	angle_diff = mlx->ray->angle - mlx->ply->ply_angle;
	if (angle_diff < 0)
		angle_diff += 2 * M_PI;
	if (angle_diff > 2 * M_PI)
		angle_diff -= 2 * M_PI;
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
