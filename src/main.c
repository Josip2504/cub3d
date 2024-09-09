/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:54:34 by jsamardz          #+#    #+#             */
/*   Updated: 2024/09/09 22:59:08 by jsamardz         ###   ########.fr       */
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
	store_map(&data, argv);
	valid_map(&data);


	printf("ok");

	//-----TEST---------------- 
	// printf("%s", data.map->no);
	// printf("%s", data.map->so);
	// printf("%s", data.map->we);
	// printf("%s", data.map->ea);
	// printf("%s", data.map->f);
	// printf("%s", data.map->c);
	// printf("\n");
	// for (int i = 0; i < data.map->rows_c; i++)
	// {
	// 	printf("%s", data.map->map[i]);
	// }
	// printf("\n");
	// printf("\n");
	// printf("%d", data.map->map[4][0]);
	//-------------------------



	return (0);
}

