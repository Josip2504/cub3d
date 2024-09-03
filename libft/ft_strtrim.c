/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilnronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:47:21 by jsamardz          #+#    #+#             */
/*   Updated: 2024/03/11 11:56:23 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ftstart(const char *s1, char const *set)
{
	size_t	i;
	size_t	len;

	i = -1;
	len = ft_strlen(s1);
	while (len > ++i)
		if (ft_strchr(set, s1[i]) == 0)
			break ;
	return (i);
}

static int	ftend(const char *s1, char const *set)
{
	size_t	i;
	size_t	len;

	i = -1;
	len = ft_strlen(s1);
	while (len > ++i)
		if (ft_strchr(set, s1[len - i - 1]) == 0)
			break ;
	return (len - i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*str;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	start = ftstart(s1, set);
	end = ftend(s1, set);
	if (start >= end)
		return (ft_strdup(""));
	str = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, (char *)s1 + start, end - start + 1);
	return (str);
}
