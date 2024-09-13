/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:04:44 by blatifat          #+#    #+#             */
/*   Updated: 2024/09/12 07:22:07 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_dbl_char(char **array)
{
	int i;

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

/* void	free_textures(t_texture *tex)
{
	mlx_delete_texture(tex->north);
	mlx_delete_texture(tex->south);
	mlx_delete_texture(tex->east);
	mlx_delete_texture(tex->west);
}
 */
void free_textures(t_texture *tex) {
    if (tex->north) {
        ft_printf("Freeing north texture...\n");
        mlx_delete_texture(tex->north);
        tex->north = NULL;
    }
    if (tex->south) {
        ft_printf("Freeing south texture...\n");
        mlx_delete_texture(tex->south);
        tex->south = NULL;
    }
    if (tex->east) {
        ft_printf("Freeing east texture...\n");
        mlx_delete_texture(tex->east);
        tex->east = NULL;
    }
    if (tex->west) {
        ft_printf("Freeing west texture...\n");
        mlx_delete_texture(tex->west);
        tex->west = NULL;
    }
}



void	free_game(t_mlx *mlx)
{
	free_dbl_char(mlx->data->map2d);
	free_textures(mlx->textur); // Free the texture struct
	free_ptr(mlx->ply);
	free_ptr(mlx->ray);
	if (mlx->imgage)
		mlx_delete_image(mlx->mlx_ptr, mlx->imgage);
	if (mlx->mlx_ptr)
		mlx_terminate(mlx->mlx_ptr);
}
