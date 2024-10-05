/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:08:51 by jsamardz          #+#    #+#             */
/*   Updated: 2024/10/05 18:55:36 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init(t_map *map)
{
	map = (t_map *)malloc(sizeof(t_map));
	if (map == NULL)
	{
		free(map);
		error_exit_nofree("Error: failed to allocate memory for map");
	}
	map->map_width = 0;
	map->map_height = 0;
	map->arg_c = 0;
	map->map2d = NULL;
	map->no = NULL;
	map->so = NULL;
	map->ea = NULL;
	map->we = NULL;
	map->f = NULL;
	map->c = NULL;
	map->player_x = 0;
	map->player_y = 0;
	map->player = '\0';
	map->player_count = 0;
}
