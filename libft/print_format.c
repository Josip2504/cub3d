/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilnronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:08:06 by jsamardz          #+#    #+#             */
/*   Updated: 2024/05/30 21:04:51 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_format(char spec, va_list ap)
{
	int	i;

	i = 0;
	if (spec == 'c')
		i += print_char(va_arg(ap, int));
	else if (spec == 's')
		i += print_str(va_arg(ap, char *));
	else if (spec == 'p')
		i += print_ptr(va_arg(ap, unsigned long), 16);
	else if (spec == 'd')
		i += print_digit(va_arg(ap, int), 10);
	else if (spec == 'i')
		i += print_digit(va_arg(ap, int), 10);
	else if (spec == 'u')
		i += print_digit((long)va_arg(ap, unsigned int), 10);
	else if (spec == 'x')
		i += print_digit((long)va_arg(ap, unsigned int), 16);
	else if (spec == 'X')
		i += print_x((long)va_arg(ap, unsigned int), 16);
	else
		i += write(1, &spec, 1);
	return (i);
}
