/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 22:52:12 by blatifat          #+#    #+#             */
/*   Updated: 2024/09/12 07:30:57 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	exit_game(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (mlx->data->map2d[i])
		free(mlx->data->map2d[i++]);
	free(mlx->data->map2d);
	free(mlx->data);
	free(mlx->ply);
	free(mlx->ray);
	mlx_delete_image(mlx->mlx_ptr, mlx->imgage);
	mlx_close_window(mlx->mlx_ptr);
	mlx_terminate(mlx->mlx_ptr);
	printf("Game closed\n");
	exit(0);
}

