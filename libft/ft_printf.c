/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilnronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:25:39 by jsamardz          #+#    #+#             */
/*   Updated: 2024/05/30 21:05:56 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	count = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			count += print_format(*(++format), ap);
			if (count < 0)
				return (-1);
		}
		else
		{
			count += print_char(*format);
			if (count < 0)
				return (-1);
		}
		++format;
	}
	va_end(ap);
	return (count);
}
