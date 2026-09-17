/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 06:24:39 by tlebon            #+#    #+#             */
/*   Updated: 2024/05/18 17:52:33 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include<stdio.h>

static double	get_decimal(const char *nptr, int index)
{
	double	decimal;
	double	unit_mult;

	decimal = 0;
	unit_mult = 10;
	while (nptr[index] && ft_isdigit(nptr[index]))
	{
		decimal += (nptr[index] - '0') / unit_mult;
		index++;
		unit_mult *= 10;
	}
	return (decimal);
}

double	ft_atof(const char *nptr)
{
	int		i;
	double	nbr;
	int		sign;

	i = 0;
	nbr = 0;
	sign = 1;
	while (ft_isspace(nptr[i]) || nptr[i] == '+' || nptr[i] == '-')
	{	
		if (nptr[i] == '-')
			sign = sign * (-1);
		i++;
	}
	while (nptr[i] && ft_isdigit(nptr[i]))
	{
		nbr = nbr * 10 + (double)(nptr[i] - '0');
		i++;
	}
	if (nptr[i] && nptr[i] == '.')
		nbr += get_decimal(nptr, i + 1);
	return (sign * nbr);
}
