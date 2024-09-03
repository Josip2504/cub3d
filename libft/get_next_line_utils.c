/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilnronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:50:31 by jsamardz          #+#    #+#             */
/*   Updated: 2024/06/02 16:28:15 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen_g(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s && s[i])
		i++;
	return (i);
}

void	ft_free_g(char **p)
{
	free(*p);
	*p = NULL;
}

int	ft_strchr_g(char *s, int c, int f)
{
	int	i;

	if (f == 1 && s == NULL)
		return (-5);
	i = 0;
	while (s && s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strnjoin_g(char *s1, char *s2, int n)
{
	char	*o;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s2[j] == '\0')
		return (NULL);
	o = malloc(ft_strlen_g(s1) + n + 1);
	if (o == NULL)
		return (NULL);
	if (s1 != NULL)
	{
		while (s1[i] != '\0')
		{
			o[i] = s1[i];
			i++;
		}
	}
	while (s2 && s2[j] != '\0' && j < n)
		o[i++] = s2[j++];
	o[i] = '\0';
	if (s1)
		ft_free_g(&s1);
	return (o);
}

char	*ft_strndup_g(char *in, int n)
{
	char	*o;
	int		i;
	int		len;

	i = 0;
	len = n;
	o = malloc(len + 1);
	if (o == NULL)
		return (NULL);
	while (in && in[i] != '\0' && i < n)
	{
		o[i] = in[i];
		i++;
	}
	o[i] = '\0';
	return (o);
}
