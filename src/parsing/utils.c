/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:26:38 by jsamardz          #+#    #+#             */
/*   Updated: 2024/10/16 11:54:01 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	parse_numbers(char *str, unsigned long numbers[3])
{
	char	*ptr;
	int		i;

	ptr = str;
	i = 0;
	while (*ptr && i < 3)
	{
		while (*ptr && (*ptr == ' ' || *ptr == ','))
			ptr++;
		while (*ptr && ft_isdigit(*ptr))
		{
			numbers[i] = numbers[i] * 10 + (*ptr - '0');
			if (numbers[i] > 255)
				return (-1);
			ptr++;
		}
		if (*ptr == ',' || *ptr == ' ' || *ptr == '\0')
			i++;
		else if (*ptr && !ft_isdigit(*ptr))
			return (-1);
	}
	return (i);
}

int	my_sscanf(char *str, int *a, int *b, int *c)
{
	unsigned long	numbers[3];
	int				result;

	numbers[0] = 0;
	numbers[1] = 0;
	numbers[2] = 0;
	result = parse_numbers(str, numbers);
	if (result != 3)
		return (1);
	*a = (int)numbers[0];
	*b = (int)numbers[1];
	*c = (int)numbers[2];
	return (0);
}

static void	char_check(t_map *map, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if ((line[i] >= '0') && (line[i] <= '9'))
			i++;
		else if ((line[i] == ',') || (ft_isspace(line[i])))
			i++;
		else
			error_exit(map, "Error: colors can only contain numbers!");
	}
}

static void	err_check(t_map *map, int c, int coma)
{
	if (c != 3)
		error_exit(map, "Error: invalid number of colors");
	if (coma != 2)
		error_exit(map, "Error: invalid commas");
}

void	line_check(t_map *map, char *line, int c, int coma)
{
	int	i;

	i = 0;
	char_check(map, line);
	while (line[i])
	{
		i = space_check(i, line);
		if (ft_isdigit(line[i]))
		{
			while (ft_isdigit(line[i++]))
			{
				if (!ft_isdigit(line[i]))
				{
					c++;
					break ;
				}
			}
		}
		if (line[i] == 44)
			coma++;
		i++;
	}
	err_check(map, c, coma);
}
