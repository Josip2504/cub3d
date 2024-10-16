/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 17:12:57 by jsamardz          #+#    #+#             */
/*   Updated: 2024/10/16 11:52:22 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	store_player(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map_height > i)
	{
		j = 0;
		while (map->map_width > j)
		{
			if (map->map2d[i][j] == 'W' || map->map2d[i][j] == 'N'
				|| map->map2d[i][j] == 'E' || map->map2d[i][j] == 'S')
			{
				map->player_count++;
				map->player_x = i;
				map->player_y = j;
			}
			j++;
		}
		i++;
	}
	if (map->player_count != 1)
		error_exit(map, "Error: player");
}

void	error_exit_nofree(char *s)
{
	ft_printf("%s\n", s);
	exit(EXIT_FAILURE);
}

void	cop(int i, int j, char *s, char *res)
{
	while (s[j])
	{
		if (s[j] == '\n')
			res[i] = '\0';
		else
			res[i] = s[j];
		i++;
		j++;
	}
}

void	free_color(t_map *map)
{
	if (map->f)
	{
		free(map->f);
		map->f = NULL;
	}
	if (map->c)
	{
		free(map->c);
		map->c = NULL;
	}
}

int	space_check(int i, char *line)
{
	if (ft_isspace(line[i]))
	{
		while (ft_isspace(line[i]))
			i++;
	}
	return (i);
}
