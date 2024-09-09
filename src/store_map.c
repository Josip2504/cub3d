/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:36:04 by jsamardz          #+#    #+#             */
/*   Updated: 2024/09/09 22:08:25 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	wloop(t_data *data, char *line, int i, int fd)
{
	int	j;

	j = 0;
	while (line != NULL)
	{
		data->map->map[i] = malloc((data->map->cols_c + 1) * sizeof(char));
		if (!data->map->map[i])
			error_exit("Error: Map alloc fail");		// potential free leak
		j = 0;
		while (line[j] != '\0')
		{
			data->map->map[i][j] = line[j];
			j++;
		}
		while (j < data->map->cols_c)
		{
			data->map->map[i][j] = '\0';
			j++;
		}
		data->map->map[i][j] = '\0';
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
	while(data->map->arg_c-- > 1)
	{
		line = get_next_line(fd);
		if (line)
			free(line);
	}
	data->map->map = malloc(data->map->rows_c * sizeof(char *));
	if (!data->map->map)
		error_exit("Error: Map alloc fail");		// potential free leak
	line = get_next_line(fd);
	wloop(data, line, i, fd);
	close(fd);
}

static void	check_wall(t_data *data, int i, int j)
{
	char	**c;

	c = data->map->map;
	if (i == 0 && (ft_strchr("0NEWS", c[i][j]) != NULL))
		error_exit("Error: invalid map");
	if (i == (data->map->rows_c - 1) && (ft_strchr("0NEWS", c[i][j]) != NULL))
		error_exit("Error: invalid map");
	if (i != 0 && i != (data->map->rows_c - 1))
	{
		if ((ft_strchr("10NEWS", c[i][j-1]) == NULL))
			error_exit("Error: invalid map");
		if ((ft_strchr("10NEWS", c[i][j+1]) == NULL))
			error_exit("Error: invalid map");
		if ((ft_strchr("10NEWS", c[i-1][j]) == NULL))
			error_exit("Error: invalid map");
		if ((ft_strchr("10NEWS", c[i+1][j]) == NULL))
			error_exit("Error: invalid map");
	}
}

void	valid_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map->rows_c > i)
	{
		j = 0;
		while (data->map->cols_c > j)
		{
			while (data->map->map[i][j] == ' ')
				j++;
			if (!(ft_strchr("10NEWS\n", data->map->map[i][j])))
				error_exit("Error: invalid map");		// potential free leak
			if (data->map->map[i][j] == '0' || data->map->map[i][j] == 'N' || data->map->map[i][j] == 'E'
				|| data->map->map[i][j] == 'W' || data->map->map[i][j] == 'S')
				check_wall(data, i, j);
			j++;
		}
		i++;
	}
}
