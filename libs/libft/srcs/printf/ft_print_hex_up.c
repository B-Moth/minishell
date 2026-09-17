/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_up.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 18:54:39 by tlebon            #+#    #+#             */
/*   Updated: 2024/01/17 11:59:46 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	count_digit(unsigned int n)
{
	int	count;

	count = 1;
	while (n > 15)
	{
		count++;
		n /= 16;
	}
	return (count);
}

static char	write_hex(long n)
{
	if (n > 9)
		return (n + 'A' - 10);
	else
		return (n + '0');
}

int	ft_print_hex_up(int i)
{
	char			*s;
	int				cursor;
	unsigned int	nbr;

	nbr = (unsigned int) i;
	s = malloc((count_digit(nbr) + 1) * sizeof(char));
	if (!s)
		return (-1);
	cursor = count_digit(nbr) - 1;
	s[cursor + 1] = '\0';
	while (nbr > 15)
	{
		s[cursor] = write_hex(nbr % 16);
		nbr /= 16;
		cursor--;
	}
	s[cursor] = write_hex(nbr);
	cursor = ft_strlen(s);
	write(1, s, cursor);
	free(s);
	return (cursor);
}
