/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilnronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 09:39:20 by jsamardz          #+#    #+#             */
/*   Updated: 2024/03/09 10:34:06 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	size_t	srclen;
	size_t	destlen;

	srclen = ft_strlen(src);
	destlen = ft_strlen(dest);
	if (destlen >= size)
		return (size + srclen);
	if (destlen == size)
		return (size + srclen);
	if (srclen < size - destlen)
		ft_memcpy(dest + destlen, src, srclen + 1);
	else
	{
		ft_memcpy(dest + destlen, src, size - destlen - 1);
		dest[size - 1] = '\0';
	}
	return (destlen + srclen);
}
