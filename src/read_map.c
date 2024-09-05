/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:15:57 by jsamardz          #+#    #+#             */
/*   Updated: 2024/09/05 13:28:34 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	correct_arg(const char *name)
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

static int	store_data(t_data *data, char *line, int flag)
{
	int	i;

	i = 0;
	while (line[i] == 32 || line[i] == 9)
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O')
		data->map->no = strdup(line);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		data->map->so = strdup(line);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		data->map->we = strdup(line);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		data->map->ea = strdup(line);
	else if (line[i] == 'F')
		data->map->f = strdup(line);
	else if (line[i] == 'C')
		data->map->c = strdup(line);
	else if (line[i] == '\n')
		flag = 0;
	else if (line[i] == '1' || line[i] == '0' || line[i] == 'S' || line[i] == 'N' || line[i] == 'E' || line[i] == 'W')
		flag = 1;
	return (flag);
}

static void	map_size(t_data *data, char *line)
{
	int	temp_len;

	temp_len = 0;
	if (!data->map->no || !data->map->ea || !data->map->we || !data->map->so || !data->map->f || !data->map->c)
		error_exit("Error: Missing textures or colors");
	data->map->rows_c++;
	temp_len = (int)ft_strlen(line);
	if (temp_len >= data->map->cols_c)
		data->map->cols_c = temp_len;
}

void	read_map(t_data *data, char **argv)
{
	int		fd;
	char	*line;
	int		flag;

	if (!correct_arg(argv[1]))
		error_exit("Error: Argument must be .cub file");
	fd = open((argv[1]), O_RDONLY);
	if (fd < 0)
		error_exit("Error: Opeining map, check does map exists");
	flag = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (flag == 0)
			flag = store_data(data, line, flag);
		if (flag == 1)
			map_size(data, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd); // you have to free strdups
}
