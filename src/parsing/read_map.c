/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:15:57 by jsamardz          #+#    #+#             */
/*   Updated: 2024/10/13 17:43:13 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	correct_arg(const char *name)
{
	const char	*end;
	size_t		name_len;
	size_t		end_len;
	size_t		res;

	end = ".cub";
	name_len = ft_strlen(name);
	end_len = ft_strlen(end);
	if (name_len < end_len)
		return (0);
	res = ft_strncmp(name + name_len - end_len, end, 4) == 0;
	return (res);
}

static int	store_data(t_map *map, char *line, int flag)
{
	int	i;

	i = 0;
	while (line[i] == 32 || line[i] == 9)
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O')
		map->no = trim(map, line, map->no);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		map->so = trim(map, line, map->so);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		map->we = trim(map, line, map->we);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		map->ea = trim(map, line, map->ea);
	else if (line[i] == 'F')
		map->f = trim(map, line, map->f);
	else if (line[i] == 'C')
		map->c = trim(map, line, map->c);
	else if (line[i] == '\n')
		flag = 0;
	else if (line[i] == '1' || line[i] == '0' || line[i] == 'S'
		|| line[i] == 'N' || line[i] == 'E' || line[i] == 'W')
		flag = 1;
	map->arg_c++;
	return (flag);
}

static int	map_size(t_map *map, char *line)
{
	int	temp_len;

	temp_len = 0;
	if (!map->no || !map->ea || !map->we || !map->so || !map->f || !map->c)
		error_exit(map, "Error: Missing textures or colors");
	if (line[0] != '\n')
		map->map_height++;
	else if (line[0] == '\n')
		return (1);
	temp_len = (int)ft_strlen(line);
	if (temp_len >= map->map_width)
		map->map_width = temp_len;
	return (0);
}

static void	check_line_more(char *line, t_map *map, int fd)
{
	int	contains_non_space;
	int	i;

	while (line != NULL)
	{
		contains_non_space = 0;
		i = 0;
		while (line[i] != '\0')
		{
			if (!ft_isspace(line[i++]))
			{
				contains_non_space = 1;
				break ;
			}
		}
		if (contains_non_space)
			error_exit(map, "Error: Invalid map");
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
}

void	read_map(t_map *map, char **argv)
{
	int		fd;
	char	*line;
	int		flag;

	fd = open((argv[1]), O_RDONLY);
	if (fd < 0)
		error_exit(map, "Error: Opeining map, check does map exists");
	flag = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (flag == 0)
			flag = store_data(map, line, flag);
		if (flag == 1)
		{
			if (map_size(map, line) == 1)
			{
				free(line);
				break ;
			}
		}
		free(line);
		line = get_next_line(fd);
	}
	line = get_next_line(fd);
	check_line_more(line, map, fd);
	close(fd);
}
