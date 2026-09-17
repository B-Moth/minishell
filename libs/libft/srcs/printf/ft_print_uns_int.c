/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uns_int.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:07:00 by tlebon            #+#    #+#             */
/*   Updated: 2023/12/04 19:16:13 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static int	ucount_digit(unsigned int n)
{
	int	count;

	count = 1;
	while (n > 9)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static char	*ft_uitoa(unsigned int u)
{
	char	*s;
	int		cursor;

	s = malloc((ucount_digit(u) + 1) * sizeof(char));
	if (!s)
		return (NULL);
	cursor = ucount_digit(u) - 1;
	s[cursor + 1] = '\0';
	while (u > 9)
	{
		s[cursor] = (u % 10) + '0';
		u /= 10;
		cursor--;
	}
	s[cursor] = u + '0';
	return (s);
}

int	ft_print_uns_int(unsigned int u)
{
	char	*s;
	int		size;

	s = ft_uitoa(u);
	if (!s)
		return (-1);
	size = ft_strlen(s);
	write(1, s, size);
	free(s);
	return (size);
}
