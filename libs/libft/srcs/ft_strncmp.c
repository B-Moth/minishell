/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:59:16 by tlebon            #+#    #+#             */
/*   Updated: 2024/05/18 18:10:37 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"
#include <stdio.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*t1;
	unsigned char	*t2;

	i = 0;
	t1 = (unsigned char *)s1;
	t2 = (unsigned char *)s2;
	while (i < n && (t1[i] || t2[i]))
	{
		if (t1[i] > t2[i])
			return (1);
		if (t1[i] < t2[i])
			return (-1);
		i++;
	}
	return (0);
}
