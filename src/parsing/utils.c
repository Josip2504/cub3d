/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:26:38 by jsamardz          #+#    #+#             */
/*   Updated: 2024/09/19 14:53:24 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	error_exit(char *s)
{
	ft_printf("%s\n", s);
	exit(EXIT_FAILURE);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
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

void	line_check(char *line)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (!ft_isdigit(line[i]) && !ft_isspace(line[i]) && line[i] != ',')
			error_exit("Error: invalid color");
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
		error_exit("Error: invalid number of colors");
}

void	cop(int i, int j, char *s, char *res)
{
	while (s[j])
	{
		if (s[j] == '\n')
			res[i] = '\0';
		else
			res[i] = s[j];
		i++;
		j++;
	}
}
