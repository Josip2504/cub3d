/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:14:25 by blatifat          #+#    #+#             */
/*   Updated: 2024/10/04 21:16:31 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


void    leaks(void)
{
    system("leaks cub3d");
}


int	main(int argc, char **argv)
{
	t_map	map;
	t_data	*data;

	atexit(leaks);
	if (argc != 2)
		error_exit("Error: incorect arguments");
	init(&map);
	read_map(&map, argv);
	store_map(&map, argv);
	valid_map(&map);
	store_player(&map);
	data = transfer_data(&map);
	init_game(data, &map);
	free_stuff(data, &map);
	return (0);
}

// invalid colors check
// leaks
// pointer being freed
// free init(map)!!!! and parsing
