/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:36:04 by jsamardz          #+#    #+#             */
/*   Updated: 2024/09/10 15:25:05 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"


// check every error_exit for leaks

static void	wloop(t_data *data, char *line, int i, int fd)
{
	int	j;

	j = 0;
	while (line != NULL)
	{
		data->map->map2d[i] = malloc((data->map->map_width + 1) * sizeof(char));
		if (!data->map->map2d[i])
			error_exit("Error: Map alloc fail");		// potential free leak
		j = 0;
		while (line[j] != '\0')
		{
			data->map->map2d[i][j] = line[j];
			j++;
		}
		while (j < data->map->map_width)
		{
			data->map->map2d[i][j] = '\0';
			j++;
		}
		data->map->map2d[i][j] = '\0';
		free(line);
		line = get_next_line(fd);
		i++;
	}
}

void	store_map(t_data *data, char **argv)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open((argv[1]), O_RDONLY);
	if (fd < 0)
		error_exit("Error: Opeining map, check does map exists");
	while (data->map->arg_c-- > 1)
	{
		line = get_next_line(fd);
		if (line)
			free(line);
	}
	data->map->map2d = malloc(data->map->map_height * sizeof(char *));
	if (!data->map->map2d)
		error_exit("Error: Map alloc fail");		// potential free leak
	line = get_next_line(fd);
	wloop(data, line, i, fd);
	close(fd);
}

static void	check_wall(t_data *data, int i, int j)
{
	char	**c;

	c = data->map->map2d;
	if (i == 0 && (ft_strchr("0NEWS", c[i][j]) != NULL))
		error_exit("Error: invalid map");
	if (i == (data->map->map_height - 1) && (ft_strchr("0NEWS", c[i][j]) != NULL))
		error_exit("Error: invalid map");
	if (i != 0 && i != (data->map->map_height - 1))
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

static void	ft_if(t_data *data, int i, int j)
{
	if (data->map->map2d[i][j] == 'N' || data->map->map2d[i][j] == 'E'
		|| data->map->map2d[i][j] == 'W' || data->map->map2d[i][j] == 'S')
	{
		data->player_count++;
		data->player = data->map->map2d[i][j];
	}
	if (!(ft_strchr("10NEWS\n", data->map->map2d[i][j])))
		error_exit("Error: invalid map");		// potential free leak
	if (data->map->map2d[i][j] == '0' || data->map->map2d[i][j] == 'N'
		|| data->map->map2d[i][j] == 'E' || data->map->map2d[i][j] == 'W'
		|| data->map->map2d[i][j] == 'S')
		check_wall(data, i, j);
}

void	valid_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map->map_height > i)
	{
		j = 0;
		while (data->map->map_width > j)
		{
			if (data->map->map2d[i][j] == ' ')
			{
				while (data->map->map2d[i][j] == ' ')
					j++;
				if (data->map->map2d[i][j] != '1')
					error_exit("Error: invalid map");
			}
			else if (data->map->map2d[i][0] != ' ' && data->map->map2d[i][0] != '1')
				error_exit("Error: invalid map");
			ft_if(data, i, j);
			j++;
		}
		i++;
	}
	if (data->player_count != 1)
		error_exit("Error: player");
}
