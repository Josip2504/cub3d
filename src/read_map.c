/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:15:57 by jsamardz          #+#    #+#             */
/*   Updated: 2024/09/03 14:17:03 by jsamardz         ###   ########.fr       */
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

void	read_map(t_data *data, char **argv)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	if (!correct_arg(argv[1]))
		error_exit("Error: Argument must be .cub file");
	fd = open((argv[1]), O_RDONLY);
	if (fd < 0)
		error_exit("Error: Opeining map, check does map exists");
	line = get_next_line(fd);
	while (line != NULL)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	printf("%d", count);
	data->player_x = 2;
}
