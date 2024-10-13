/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:09:14 by jsamardz          #+#    #+#             */
/*   Updated: 2024/10/13 17:29:27 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

static void	free_2d(int i, t_map *map)
{
	while (i < map->map_height)
	{
		if (map->map2d[i])
			free(map->map2d[i]);
		i++;
	}
	free(map->map2d);
}

void	free_map(t_map *map, int i)
{
	if (map == NULL)
	{
		free(map);
		return ;
	}
	if (map->map2d)
		free_2d(i, map);
	if (map->no)
		free(map->no);
	if (map->so)
		free(map->so);
	if (map->we)
		free(map->we);
	if (map->ea)
		free(map->ea);
	if (map->f)
		free(map->f);
	if (map->c)
		free(map->c);
	if (map)
		free(map);
}

void	error_exit(t_map *map, char *s)
{
	int	i;

	i = 0;
	ft_printf("%s\n", s);
	free_map(map, i);
	exit(EXIT_FAILURE);
}

int	help(int i, unsigned long numbers[3])
{
	while (i < 3)
	{
		numbers[i] = 0;
		i++;
	}
	i = 0;
	return (i);
}
