/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:14:25 by blatifat          #+#    #+#             */
/*   Updated: 2024/10/07 19:26:07 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void leaks(void)
{
	system("leaks cub3d");
}

int	main(int argc, char **argv)
{
	t_map	*map;
	t_data	*data;

	if (argc != 2)
		error_exit_nofree("Error: incorect arguments");
	if (!correct_arg(argv[1]))
		error_exit_nofree("Error: Argument must be .cub file");
	map = (t_map *)malloc(sizeof(t_map));
	if (map == NULL)
		error_exit(map, "Error: failed to allocate for map");
	init(map);
	read_map(map, argv);
	store_map(map, argv);
	valid_map(map);
	store_player(map);
	data = transfer_data(map);
	init_game(data, map);
	return (0);
}
