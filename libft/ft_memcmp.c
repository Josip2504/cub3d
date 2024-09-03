/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilnronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:54:50 by jsamardz          #+#    #+#             */
/*   Updated: 2024/05/30 21:13:52 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;
	size_t				i;

	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	i = 0;
	while (n > i && *(str1 + i) == *(str2 + i))
		i++;
	if (n == i)
		return (0);
	return (*(str1 + i) - *(str2 + i));
}
