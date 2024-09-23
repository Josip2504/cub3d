/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:11:14 by jsamardz          #+#    #+#             */
/*   Updated: 2024/09/19 14:51:37 by jsamardz         ###   ########.fr       */
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
				map->player_x = i;
				map->player_y = j;
			}
			j++;
		}
		i++;
	}
}

static int	help(char *s, int i)
{
	while (s[i++])
	{
		if (s[i] == 32 || s[i] == 9 || s[i] == '\0')
			break ;
	}
	return (i);
}

char	*trim(char *s)
{
	int		i;
	int		j;
	char	*res;
	int		len;

	i = 0;
	len = 0;
	res = NULL;
	while (s[i] == 32 || s[i] == 9)
		i++;
	i = help(s, i);
	while (s[i] == 32 || s[i] == 9)
		i++;
	if (s[i] == '\0' || s[i] == '\n')
		error_exit("Error: Missing textures");
	j = i;
	while (s[i++])
		len++;
	res = ft_calloc(len, sizeof(char *));
	if (!res)
		error_exit("Error: malloc");
	i = 0;
	cop(i, j, s, res);
	return (res);
}

static void	ft_color(t_map *map, t_data *data)
{
	int	i;

	i = 0;
	line_check(map->f);
	line_check(map->c);
	my_sscanf(map->f, &data->floor[0], &data->floor[1], &data->floor[2]);
	my_sscanf(map->c, &data->ceil[0], &data->ceil[1], &data->ceil[2]);
	while (i < 3)
	{
		if (data->ceil[i] > 255 || data->floor[i] > 255)
			error_exit("Error: too big color number");
		i++;
	}
}

t_data	*transfer_data(t_map *map)
{
	int		i;
	t_data	*dt;

	i = 0;
	dt = calloc(1, sizeof(t_data));
	dt->map2d = calloc(map->map_height, sizeof(char *));
	while (i < map->map_height)
	{
		dt->map2d[i] = ft_strdup(map->map2d[i]);
		i++;
	}
	dt->ply_x = map->player_x;
	dt->ply_y = map->player_y;
	dt->height_map = map->map_height;
	dt->width_map = map->map_width - 1;
	ft_color(map, dt);
	return (dt);
}
