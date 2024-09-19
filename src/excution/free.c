/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:04:44 by blatifat          #+#    #+#             */
/*   Updated: 2024/09/19 12:15:51 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_dbl_char(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_ptr(void *ptr)
{
	if (ptr)
		free(ptr);
}

void	free_textures(t_texture *tex)
{
	mlx_delete_texture(tex->north);
	mlx_delete_texture(tex->south);
	// mlx_delete_texture(tex->east);
	mlx_delete_texture(tex->west);
}

void	free_game(t_mlx *mlx)
{
	free_dbl_char(mlx->data->map2d);
	free_textures(mlx->textur);
	free_ptr(mlx->ply);
	free_ptr(mlx->ray);
	if (mlx->imgage)
		mlx_delete_image(mlx->mlx_ptr, mlx->imgage);
	if (mlx->mlx_ptr)
		mlx_terminate(mlx->mlx_ptr);
}
