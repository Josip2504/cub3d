/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:54:34 by jsamardz          #+#    #+#             */
/*   Updated: 2024/09/04 21:55:26 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		error_exit("Error: incorect arguments");
	init(&data);
	read_map(&data, argv);


	printf("%s", data.map->no);
	printf("%s", data.map->so);
	printf("%s", data.map->we);
	printf("%s", data.map->ea);
	printf("%s", data.map->f);
	printf("%s", data.map->c);

	// printf("%c", data.map->map[0][0]);

	return (0);
}
