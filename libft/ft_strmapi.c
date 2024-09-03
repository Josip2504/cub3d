/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilnronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:05:53 by jsamardz          #+#    #+#             */
/*   Updated: 2024/03/12 15:23:51 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len;
	char	*res;

	i = -1;
	len = ft_strlen(s);
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (++i < len)
		res[i] = (*f)(i, s[i]);
	res[i] = '\0';
	return (res);
}
