/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 23:56:19 by blatifat          #+#    #+#             */
/*   Updated: 2024/10/04 19:20:24 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	verify_circle(float angle, char c)
{
	if (c == 'x')
		return (angle > 0 && angle < M_PI);
	if (c == 'y')
		return (angle > M_PI / 2 && angle < 3 * M_PI / 2);
	return (0);
}

int	evaluate_intersection(float angle, float *inter, float *step, int horiz)
{
	int	is_positive_direction;

	if (horiz)
		is_positive_direction = (angle > 0 && angle < M_PI);
	else
		is_positive_direction = !(angle > M_PI / 2 && angle < 3 * M_PI / 2);
	if (is_positive_direction)
	{
		*inter += TILE_SIZE;
		return (-1);
	}
	*step *= (-1);
	return (1);
}
