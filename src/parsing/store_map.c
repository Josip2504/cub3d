/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:36:04 by jsamardz          #+#    #+#             */
/*   Updated: 2024/10/13 17:22:10 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	wloop(t_map *map, char *line, int i, int fd)
{
	int	j;

	j = 0;
	while (line != NULL)
	{
		if (line[0] == '\n')
		{
			free(line);
			break ;
		}
		map->map2d[i] = malloc((map->map_width + 1) * sizeof(char));
		if (!map->map2d[i])
			error_exit(map, "Error: Map alloc fail");
		j = 0;
		while (line[j] != '\0')
		{
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
	if (map->map2d[i][0] != 32 && map->map2d[i][0] != '1')
		error_exit(map, "Error: invalid map");
	if (map->map2d[i][j] == ' ')
	{
		while (j < map->map_width && map->map2d[i][j] == ' ')
			j++;
		if (j < map->map_width && map->map2d[i][j] != '1')
			error_exit(map, "Error: invalid map");
	}
	else if (map->map2d[i][j] == 'N' || map->map2d[i][j] == 'E'
		|| map->map2d[i][j] == 'W' || map->map2d[i][j] == 'S')
		map->player = map->map2d[i][j];
	if (!(ft_strchr("10NEWS\n", map->map2d[i][j])))
		error_exit(map, "Error: invalid map");
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
	while (i < map->map_height)
	{
		j = 0;
		while (j < map->map_width && map->map2d[i][j] == ' ')
			j++;
		while (j < map->map_width)
		{
			ft_if(map, i, j);
			j++;
		}
		i++;
	}
}

void	check_wall(t_map *map, int i, int j)
{
	char	**c;

	c = map->map2d;
	if (i == 0 && (ft_strchr("0NEWS", c[i][j]) != NULL))
		error_exit(map, "Error: invalid map");
	if (i == (map->map_height - 1) && (ft_strchr("0NEWS", c[i][j]) != NULL))
		error_exit(map, "Error: invalid map");
	if (i != 0 && i != (map->map_height - 1))
	{
		if ((ft_strchr("10NEWS", c[i][j - 1]) == NULL))
			error_exit(map, "Error: invalid map");
		if ((ft_strchr("10NEWS", c[i][j + 1]) == NULL))
			error_exit(map, "Error: invalid map");
		if ((ft_strchr("10NEWS", c[i - 1][j]) == NULL))
			error_exit(map, "Error: invalid map");
		if ((ft_strchr("10NEWS", c[i + 1][j]) == NULL))
			error_exit(map, "Error: invalid map");
	}
}
