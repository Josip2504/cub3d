/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilnronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:25:45 by jsamardz          #+#    #+#             */
/*   Updated: 2024/03/12 20:54:18 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	ft_loop(int res, int len, char *str)
{
	while (len > 0 && res > 0)
	{
		len--;
		*(str + len) = res % 10 + '0';
		res = res / 10;
	}
}

char	*ft_itoa(int n)
{
	long int	res;
	size_t		len;
	char		*str;

	len = ft_len(n);
	res = n;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	*(str + len) = 0;
	if (n < 0)
	{
		*(str + 0) = '-';
		res *= -1;
	}
	ft_loop(res, len, str);
	return (str);
}
