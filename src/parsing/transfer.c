/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:11:14 by jsamardz          #+#    #+#             */
/*   Updated: 2024/10/13 19:19:09 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	help1(char *s, int i)
{
	while (s[i++])
	{
		if (s[i] == 32 || s[i] == 9 || s[i] == '\0')
			break ;
	}
	return (i);
}

char	*trim(t_map *map, char *s, char *dest)
{
	int		i;
	int		j;
	char	*res;
	int		len;

	i = 0;
	len = 0;
	res = NULL;
	check_dest(dest, map);
	while (s[i] == 32 || s[i] == 9)
		i++;
	i = help1(s, i);
	while (s[i] == 32 || s[i] == 9)
		i++;
	if (s[i] == '\0' || s[i] == '\n')
		error_exit(map, "Error: Missing textures");
	j = i;
	while (s[i++])
		len++;
	res = ft_calloc(len, sizeof(char *));
	if (!res)
		error_exit(map, "Error: malloc");
	i = 0;
	cop(i, j, s, res);
	return (res);
}

static void	ft_color(t_map *map, t_data *data)
{
	int	i;
	int	c;
	int	coma;
	int	f;

	i = 0;
	c = 0;
	coma = 0;
	f = 0;
	line_check(map, map->f, c, coma);
	line_check(map, map->c, c, coma);
	f = my_sscanf(map->f, &data->floor[0], &data->floor[1], &data->floor[2]);
	if (f == 1)
		error_exit(map, "Error: Invalid color");
	f = my_sscanf(map->c, &data->ceil[0], &data->ceil[1], &data->ceil[2]);
	if (f == 1)
		error_exit(map, "Error: Invalid color");
	while (i < 3)
	{
		if (data->ceil[i] > 255 || data->floor[i] > 255)
			error_exit(map, "Error: too big color number");
		i++;
	}
}

void	valid_m(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->height_map)
	{
		j = 0;
		while (j < data->width_map)
		{
			if (data->map2d[i][j] == 10)
			{
				while (data->map2d[i][j])
				{
					data->map2d[i][j] = 0;
					j++;
				}
			}
			else
				j++;
		}
		i++;
	}
}

t_data	*transfer_data(t_map *map)
{
	t_data	*dt;

	dt = malloc(1 * sizeof(t_data));
	dt->map2d = map->map2d;
	dt->ply_x = map->player_x;
	dt->ply_y = map->player_y;
	dt->height_map = map->map_height;
	dt->width_map = map->map_width - 1;
	valid_m(dt);
	ft_color(map, dt);
	free_color(map);
	return (dt);
}
