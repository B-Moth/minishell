/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:57:18 by tlebon            #+#    #+#             */
/*   Updated: 2023/11/24 17:27:30 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	d_size;
	size_t	s_size;

	if (size == 0)
		return (ft_strlen(src));
	if ((!dest || !src) || size <= ft_strlen(dest))
		return (ft_strlen(src) + size);
	if (src[0] == '\0')
		return (ft_strlen(dest));
	d_size = ft_strlen(dest);
	s_size = ft_strlen(src);
	i = d_size;
	while (src[i - d_size] && i < size - 1)
	{
		dest[i] = src[i - d_size];
		i++;
	}
	dest[i] = '\0';
	return (s_size + d_size);
}
