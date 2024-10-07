/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:26:38 by jsamardz          #+#    #+#             */
/*   Updated: 2024/10/07 20:03:59 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	free_2d(int i, t_map *map)
{
	while (i <= map->map_height)
	{
		if (map->map2d[i])
			free(map->map2d[i]);
		i++;
	}
	free(map->map2d);
}

void	free_map(t_map *map, int i)
{
	if (map == NULL)
		return ;
	if (map->map2d)
		free_2d(i, map);
	if (map->no)
		free(map->no);
	if (map->so)
		free(map->so);
	if (map->we)
		free(map->we);
	if (map->ea)
		free(map->ea);
	if (map->f)
		free(map->f);
	if (map->c)
		free(map->c);
	if (map)
		free(map);
}

void	error_exit(t_map *map, char *s)
{
	int	i;

	i = 0;
	free_map(map, i);
	ft_printf("%s\n", s);
	exit(EXIT_FAILURE);
}

void	my_sscanf(char *str, int *a, int *b, int *c)
{
	int		numbers[3];
	int		i;
	char	*ptr;

	ptr = str;
	i = 0;
	numbers[0] = 0;
	numbers[1] = 0;
	numbers[2] = 0;
	while (*ptr && i < 3)
	{
		while (*ptr && !ft_isdigit(*ptr))
			ptr++;
		while (*ptr && ft_isdigit(*ptr))
		{
			numbers[i] = numbers[i] * 10 + (*ptr - '0');
			ptr++;
		}
		i++;
	}
	*a = numbers[0];
	*b = numbers[1];
	*c = numbers[2];
}

void	line_check(t_map *map, char *line)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	char_check(map, line);
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (!ft_isdigit(line[i]) && !ft_isspace(line[i]) && line[i] != ',')
			error_exit(map, "Error: invalid color");
		while (ft_isdigit(line[i++]))
		{
			if (!ft_isdigit(line[i]))
			{
				c++;
				break ;
			}
		}
		i++;
	}
	if (c != 3)
		error_exit(map, "Error: invalid number of colors");
}
