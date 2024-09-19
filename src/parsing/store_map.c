/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:36:04 by jsamardz          #+#    #+#             */
/*   Updated: 2024/09/19 12:28:22 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	wloop(t_map *map, char *line, int i, int fd)
{
	int	j;

	j = 0;
	while (line != NULL)
	{
		map->map2d[i] = malloc((map->map_width + 1) * sizeof(char));
		if (!map->map2d[i])
			error_exit("Error: Map alloc fail");
		j = 0;
		while (line[j] != '\0')
		{
			map->map2d[i][j] = line[j];
			j++;
		}
		while (j < map->map_width)
		{
			map->map2d[i][j] = '\0';
			j++;
		}
		map->map2d[i][j] = '\0';
		free(line);
		line = get_next_line(fd);
		i++;
	}
}

void	store_map(t_map *map, char **argv)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open((argv[1]), O_RDONLY);
	if (fd < 0)
		error_exit("Error: Opeining map, check does map exists");
	while (map->arg_c-- > 1)
	{
		line = get_next_line(fd);
		if (line)
			free(line);
	}
	map->map2d = malloc(map->map_height * sizeof(char *));
	if (!map->map2d)
		error_exit("Error: Map alloc fail");		// potential free leak
	line = get_next_line(fd);
	wloop(map, line, i, fd);
	close(fd);
}

static void	check_wall(t_map *map, int i, int j)
{
	char	**c;

	c = map->map2d;
	if (i == 0 && (ft_strchr("0NEWS", c[i][j]) != NULL))
		error_exit("Error: invalid map");
	if (i == (map->map_height - 1) && (ft_strchr("0NEWS", c[i][j]) != NULL))
		error_exit("Error: invalid map");
	if (i != 0 && i != (map->map_height - 1))
	{
		if ((ft_strchr("10NEWS", c[i][j - 1]) == NULL))
			error_exit("Error: invalid map");
		if ((ft_strchr("10NEWS", c[i][j + 1]) == NULL))
			error_exit("Error: invalid map");
		if ((ft_strchr("10NEWS", c[i - 1][j]) == NULL))
			error_exit("Error: invalid map");
		if ((ft_strchr("10NEWS", c[i + 1][j]) == NULL))
			error_exit("Error: invalid map");
	}
}

static void	ft_if(t_map *map, int i, int j)
{
	if (map->map2d[i][j] == 'N' || map->map2d[i][j] == 'E'
		|| map->map2d[i][j] == 'W' || map->map2d[i][j] == 'S')
	{
		map->player_count++;
		map->player = map->map2d[i][j];
	}
	if (!(ft_strchr("10NEWS\n", map->map2d[i][j])))
		error_exit("Error: invalid map");
	if (map->map2d[i][j] == '0' || map->map2d[i][j] == 'N'
		|| map->map2d[i][j] == 'E' || map->map2d[i][j] == 'W'
		|| map->map2d[i][j] == 'S')
		check_wall(map, i, j);
}

void	valid_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map_height > i)
	{
		j = 0;
		while (map->map_width > j)
		{
			if (map->map2d[i][j] == ' ')
			{
				while (map->map2d[i][j] == ' ')
					j++;
				if (map->map2d[i][j] != '1')
					error_exit("Error: invalid map");
			}
			else if (map->map2d[i][0] != ' ' && map->map2d[i][0] != '1')
				error_exit("Error: invalid map");
			ft_if(map, i, j);
			j++;
		}
		i++;
	}
	if (map->player_count != 1)
		error_exit("Error: player");
}
