/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_digit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilnronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:13:15 by jsamardz          #+#    #+#             */
/*   Updated: 2024/05/30 21:04:54 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_help(long n)
{
	char	*symbol;
	int		test;

	symbol = "0123456789abcdef";
	test = 0;
	test = (write(1, &symbol[n], 1));
	return (test);
}

int	print_digit(long n, int base)
{
	int		i;
	int		test;

	test = 0;
	if (n < 0)
	{
		test += (write(1, "-", 1));
		if (test < 0)
			return (-1);
		return ((print_digit(-n, base) + 1));
	}
	else if (n < base)
	{
		test = ft_help(n);
		if (test < 0)
			return (-1);
		return (test);
	}
	else
	{
		i = print_digit(n / base, base);
		if (i < 0)
			return (-1);
		return (i + print_digit(n % base, base));
	}
}
