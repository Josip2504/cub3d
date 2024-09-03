/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilnronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:44:18 by jsamardz          #+#    #+#             */
/*   Updated: 2024/05/30 21:05:01 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_help_x(long n)
{
	char	*symbol;
	int		test;

	symbol = "0123456789ABCDEF";
	test = 0;
	test += (write(1, &symbol[n], 1));
	return (test);
}

int	print_x(long n, int base)
{
	int		i;
	int		test;

	test = 0;
	if (n < 0)
	{
		test += (write(1, "-", 1));
		if (test < 0)
			return (-1);
		return (print_x(-n, base) + 1);
	}
	else if (n < base)
	{
		test = ft_help_x(n);
		if (test < 0)
			return (-1);
		return (test);
	}
	else
	{
		i = print_x(n / base, base);
		if (i < 0)
			return (-1);
		return (i + print_x(n % base, base));
	}
}
