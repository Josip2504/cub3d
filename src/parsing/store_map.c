/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:36:04 by jsamardz          #+#    #+#             */
/*   Updated: 2024/10/07 14:50:22 by jsamardz         ###   ########.fr       */
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
			error_exit(map, "Error: Map alloc fail");
		j = 0;
		while (line[j] != '\0')
		{
			if (line[j] == 32)
				map->map2d[i][j] = '1';
			else
				map->map2d[i][j] = line[j];
			map->map2d[i][j] = line[j];
			j++;
		}
		while (j < map->map_width)
			map->map2d[i][j++] = '\0';
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
		error_exit(map, "Error: Opeining map, check does map exists");
	while (map->arg_c-- > 1)
	{
		line = get_next_line(fd);
		if (line)
			free(line);
	}
	map->map2d = malloc(map->map_height * sizeof(char *));
	if (!map->map2d)
		error_exit(map, "Error: Map alloc fail");
	line = get_next_line(fd);
	wloop(map, line, i, fd);
	close(fd);
}

static void	ft_if(t_map *map, int i, int j)
{
	if (map->map2d[i][j] == ' ')
	{
		while (j < map->map_width && map->map2d[i][j] == ' ')
			j++;
		if (j < map->map_width && map->map2d[i][j] != '1')
			error_exit(map, "Error: invalid map");
	}
	else if (j == 0 && map->map2d[i][0] != ' ' && map->map2d[i][0] != '1')
		error_exit(map, "Error: invalid map");
	if (map->map2d[i][j] == 'N' || map->map2d[i][j] == 'E'
		|| map->map2d[i][j] == 'W' || map->map2d[i][j] == 'S')
		map->player = map->map2d[i][j];
	if (!(ft_strchr("10NEWS\n", map->map2d[i][j])))
		error_exit(map, "Error: invalid map");
	if (map->map2d[i][j] == '0' || map->map2d[i][j] == 'N'
		|| map->map2d[i][j] == 'E' || map->map2d[i][j] == 'W'
		|| map->map2d[i][j] == 'S')
		check_wall(map, i, j);
}

static void	help(int empty_line_encountered, int j, int i, t_map *map)
{
	if (empty_line_encountered)
		error_exit(map, "Error: invalid map");
	while (j < map->map_width)
	{
		ft_if(map, i, j);
		j++;
	}
}

void	valid_map(t_map *map)
{
	int	i;
	int	j;
	int	empty_line_encountered;

	i = 0;
	empty_line_encountered = 0;
	while (i < map->map_height)
	{
		j = 0;
		while (j < map->map_width && map->map2d[i][j] == ' ')
			j++;
		if (j == map->map_width || map->map2d[i][j] == '\n')
		{
			if (i > 0 && (j == 0 || map->map2d[i][0] == '\n'))
				empty_line_encountered = 1;
		}
		else
			help(empty_line_encountered, j, i, map);
		i++;
	}
}
