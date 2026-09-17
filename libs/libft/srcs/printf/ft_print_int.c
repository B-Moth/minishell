/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:01:35 by tlebon            #+#    #+#             */
/*   Updated: 2023/12/04 19:09:37 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

int	ft_print_int(int n)
{
	char	*s;
	int		size;

	s = ft_itoa(n);
	if (!s)
		return (-1);
	size = ft_strlen(s);
	write(1, s, size);
	free(s);
	return (size);
}
