/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:14:25 by blatifat          #+#    #+#             */
/*   Updated: 2024/09/13 17:37:43 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_map	map;
	t_data	*data;

	if (argc != 2)
		error_exit("Error: incorect arguments");
	init(&map);
	read_map(&map, argv);
	store_map(&map, argv);
	valid_map(&map);
	store_player(&map);
	printf("Map parsing ok\n");
	data = transfer_data(&map);
	printf("%s", map.no);
	printf("%s", map.we);
	printf("%s", map.so);
	printf("%s", map.ea);
	printf("transfer ok so far\n");
	init_game(data);
	return (0);
}
