/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilnronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:29:41 by jsamardz          #+#    #+#             */
/*   Updated: 2024/03/10 17:43:52 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	s1len;
	size_t	s2len;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	result = (char *)malloc((s1len + s2len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, s1len);
	ft_memcpy(result + s1len, s2, s2len);
	result[s1len + s2len] = '\0';
	return (result);
}
