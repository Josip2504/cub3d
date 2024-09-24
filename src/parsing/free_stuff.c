/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:56:18 by jsamardz          #+#    #+#             */
/*   Updated: 2024/09/24 12:15:19 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	free_map(t_map *map)
{
	int	i;
	
	if (map == NULL)
		return;
	if (map->map2d != NULL)
	{
		i = 0;
		while (i < map->map_height)
		{
			free(map->map2d[i]);
			i++;
		}
		free(map->map2d);
	}
	// free(map->no);
	// free(map->so);
	// free(map->we);
	// free(map->ea);
	// free(map->f);
	// free(map->c);
	// free(map);
}

void	free_stuff(t_data *data, t_map *map)
{
	(void)data;
	free_map(map);
}
