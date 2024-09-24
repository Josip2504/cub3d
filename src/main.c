/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:14:25 by blatifat          #+#    #+#             */
/*   Updated: 2024/09/24 14:31:34 by jsamardz         ###   ########.fr       */
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

	// atexit(leaks);
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

// so, ea working fine
// we, no acting weird
// probably north
// invalid colors check
// subject map seg faluts
// leaks
// pointer being freed
// free init(map)!!!! and parsing