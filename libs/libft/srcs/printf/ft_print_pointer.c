/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:04:55 by tlebon            #+#    #+#             */
/*   Updated: 2024/01/17 12:02:21 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

static int	count_digit(unsigned long n)
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

static char	write_hex(unsigned long n)
{
	if (n > 9)
		return (n + 'a' - 10);
	else
		return (n + '0');
}

char	*ultohexa(unsigned long adr)
{
	int		cursor;
	char	*s;

	s = malloc((count_digit(adr) + 1) * sizeof(char));
	if (!s)
		return (NULL);
	cursor = count_digit(adr) - 1;
	s[cursor + 1] = '\0';
	while (adr > 15)
	{
		s[cursor] = write_hex(adr % 16);
		adr /= 16;
		cursor--;
	}
	s[cursor] = write_hex(adr);
	return (s);
}

int	ft_print_pointer(unsigned long p)
{
	char	*s;
	int		adr;

	if (!p)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	else
	{
		write(1, "0x", 2);
		s = ultohexa(p);
	}
	if (!s)
		return (-1);
	adr = ft_strlen(s);
	write(1, s, adr);
	free(s);
	return (adr + 2);
}
