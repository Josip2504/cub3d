/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:36:04 by jsamardz          #+#    #+#             */
/*   Updated: 2024/09/05 15:19:08 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	store_map(t_data *data, char **argv)
{
	int		fd;
	char	*line;
	int		i;
	int		j;

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
		data->map->map[i][j] = '\0';
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
}
