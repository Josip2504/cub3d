/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:14:25 by blatifat          #+#    #+#             */
/*   Updated: 2024/09/19 13:51:28 by jsamardz         ###   ########.fr       */
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
	data = transfer_data(&map);
	init_game(data, &map);
	return (0);
}
