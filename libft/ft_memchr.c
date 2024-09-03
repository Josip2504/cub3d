/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilnronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:41:02 by jsamardz          #+#    #+#             */
/*   Updated: 2024/05/30 21:13:48 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	to_find;

	i = 0;
	str = (unsigned char *) s;
	to_find = (unsigned char) c;
	while (n > i)
	{
		if (str[i] == to_find)
			return ((void *) &str[i]);
		i++;
	}
	return (NULL);
}
