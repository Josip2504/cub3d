/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:08:51 by jsamardz          #+#    #+#             */
/*   Updated: 2024/09/04 22:01:16 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init(t_data *data)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (map == NULL)
	{
		free(map);
		error_exit("Error: failed to allocate memory for map");
	}
	map->no = NULL;
	map->so = NULL;
	map->ea = NULL;
	map->we = NULL;
	map->f = NULL;
	map->c = NULL;
	map->map = NULL;
	data->mlx = NULL;
	data->win = NULL;
	data->player_x = 0;
	data->player_y = 0;
	data->map = map;
	data->map->cols_c = 0;
	data->map->rows_c = 0;
	data->map->rows = NULL;
}
