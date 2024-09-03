/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilnronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 15:43:57 by jsamardz          #+#    #+#             */
/*   Updated: 2024/03/10 16:56:31 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	size_t			i;
	unsigned int	slen;

	i = -1;
	slen = ft_strlen(s);
	if (!s)
		return (NULL);
	if (start >= slen)
		return (ft_strdup(""));
	if (len > (slen - start))
		len = (slen - start);
	sub = ft_calloc(len + 1, sizeof(char));
	if (!sub)
		return (NULL);
	while (len > ++i)
		sub[i] = s[i + start];
	sub[i] = '\0';
	return (sub);
}
