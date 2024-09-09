/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:54:51 by jsamardz          #+#    #+#             */
/*   Updated: 2024/09/09 22:24:57 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>

typedef struct	t_map
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
	char	**map;
	int		rows_c;
	int		cols_c;
	int		arg_c;
}	t_map;

typedef struct	s_data
{
	void	*mlx;
	void	*win;
	char	player;
	int		player_count;
	int		player_x;
	int		player_y;
	t_map	*map;
}	t_data;

// utils.c
void	error_exit(char *s);

// init.c
void	init(t_data *data);

// read_map.c
void	read_map(t_data *data, char **argv);

// store_map.c
void	store_map(t_data *data, char **argv);
void	valid_map(t_data *data);

#endif