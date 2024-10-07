/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 17:12:57 by jsamardz          #+#    #+#             */
/*   Updated: 2024/10/07 14:57:40 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

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

void	char_check(t_map *map, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if ((line[i] >= '0') && (line[i] <= '9'))
			i++;
		else if ((line[i] == ',') || (ft_isspace(line[i])))
			i++;
		else
			error_exit(map, "Error: colors can only contain numbers!");
	}
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
