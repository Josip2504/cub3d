/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilnronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:50:42 by jsamardz          #+#    #+#             */
/*   Updated: 2024/06/02 16:28:31 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc_g(size_t a, size_t b)
{
	char			*p;
	unsigned int	i;
	size_t			x;

	i = 0;
	x = a * b;
	p = (char *)malloc(x);
	if (p == NULL)
		return (0);
	while (i < x)
	{
		p[i] = 0;
		i++;
	}
	return (p);
}

char	*ft_up(char **nl, int pos)
{
	char	*temp;
	int		len;

	len = ft_strlen_g(*nl) - pos;
	temp = ft_strndup_g(*nl + pos, len);
	ft_free_g(nl);
	*nl = temp;
	return (*nl);
}

char	*ft_output_g(char **nl, int pos, int b)
{
	char	*line;

	if (((b == 0 || b == -1) && *nl == NULL) || pos == -5)
	{
		if (*nl)
			return (*nl);
		return (NULL);
	}
	line = NULL;
	if (pos == -1)
		pos = ft_strlen_g(*nl);
	else
		pos++;
	line = ft_strndup_g(*nl, pos);
	if (pos == ft_strlen_g(*nl))
		ft_free_g(nl);
	else
		*nl = ft_up(nl, pos);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stat;
	int			pos;
	int			b;

	if (fd < 0 || BUFFER_SIZE < 0 || fd > 10240)
		return (NULL);
	line = NULL;
	pos = ft_strchr_g(stat, '\n', 0);
	while (pos == -1 && pos != -5)
	{
		line = ft_calloc_g(BUFFER_SIZE + 1, 1);
		if (line == NULL)
			return (NULL);
		b = read(fd, line, BUFFER_SIZE);
		if (b == 0 || b == -1)
			break ;
		stat = ft_strnjoin_g(stat, line, b);
		pos = ft_strchr_g(stat, '\n', 1);
		ft_free_g(&line);
	}
	ft_free_g(&line);
	return (ft_output_g(&stat, pos, b));
}
