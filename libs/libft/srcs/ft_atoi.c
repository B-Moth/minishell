/* ************************************************************************** */
/*	                                                                        */
/*	                                                    :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*	                                                +:+ +:+         +:+     */
/*   By: tlebon <marvin@42.fr>	                  +#+  +:+       +#+        */
/*	                                            +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:01:00 by tlebon	        #+#    #+#             */
/*   Updated: 2023/11/17 16:28:17 by tlebon           ###   ########.fr       */
/*	                                                                        */
/* ************************************************************************** */
#include"libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	nbr;
	int	sign;

	i = 0;
	nbr = 0;
	sign = 1;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-')
		sign = sign * (-1);
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while (ft_isdigit(nptr[i]))
	{
		nbr = nbr * 10 + (nptr[i] - '0');
		i++;
	}
	return (sign * nbr);
}
