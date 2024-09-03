/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilnronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:28:49 by jsamardz          #+#    #+#             */
/*   Updated: 2024/03/12 22:18:34 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	product;
	void	*memory;

	product = count * size;
	memory = malloc(product);
	if (!memory)
		return (NULL);
	ft_bzero(memory, product);
	return (memory);
}
