/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 22:52:12 by blatifat          #+#    #+#             */
/*   Updated: 2024/10/13 16:48:01 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	handle_file_errors(int errnum)
{
	const char	*error_messages[] = {
		"Error\n Wrong number of arguments\n",
		"Error\n filename too long or too short\n",
		"Error\n Wrong extension (file must have .cub extension)\n",
		"Error\n Unable to open file: %s\n"
	};

	if (errnum >= 1 && errnum <= FILE_OPEN)
	{
		if (errnum == FILE_OPEN)
			ft_printf(error_messages[errnum - 1], strerror(errno));
		else
			ft_printf("%s", error_messages[errnum - 1]);
		exit(EXIT_FAILURE);
	}
}

static void	handle_map_errors(int errnum)
{
	const char	*error_messages[] = {
		"Error\n Invalid map description\n",
		"Error\n Invalid map\n",
		"Error\n Failed to load textures\n"
	};

	if (errnum >= MAP_DESCRIPTION && errnum <= LOAD_TEXTURES)
	{
		ft_printf("%s", error_messages[errnum - MAP_DESCRIPTION]);
		exit(EXIT_FAILURE);
	}
}

int	error(int errnum)
{
	if (errnum <= FILE_OPEN)
		handle_file_errors(errnum);
	else
		handle_map_errors(errnum);
	return (0);
}

void	exit_game(t_mlx *mlx)
{
	int	i;

	i = 0;
	if (mlx->data->map2d)
	{
		while (i < mlx->data->height_map)
		{
			if (mlx->data->map2d[i])
				free(mlx->data->map2d[i]);
			i++;
		}
		free(mlx->data->map2d);
	}
	if (mlx->data)
		free(mlx->data);
	if (mlx->ply)
		free(mlx->ply);
	if (mlx->ray)
		free(mlx->ray);
	mlx_delete_image(mlx->mlx_ptr, mlx->imgage);
	mlx_close_window(mlx->mlx_ptr);
	mlx_terminate(mlx->mlx_ptr);
	printf("Game closed\n");
	exit(0);
}
