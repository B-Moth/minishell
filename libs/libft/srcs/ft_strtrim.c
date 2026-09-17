/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:21:54 by tlebon            #+#    #+#             */
/*   Updated: 2023/12/06 16:40:24 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

static int	find_start(char const *s, char const *set)
{
	size_t	i;
	size_t	p;

	i = 0;
	while (s[i])
	{
		p = 0;
		while (set[p])
		{
			if (s[i] == set[p])
				break ;
			p++;
		}
		if (p == ft_strlen(set))
			return (i);
		i++;
	}
	return (-1);
}

static int	find_end(char const *s, char const *set)
{
	size_t	i;
	size_t	p;

	i = ft_strlen(s) - 1;
	while (i > 0)
	{
		p = 0;
		while (set[p])
		{
			if (s[i] == set[p])
				break ;
			p++;
		}
		if (p == ft_strlen(set))
			return (i);
		i--;
	}
	return (-1);
}

char	*ft_strtrim(char const *s, char const *set)
{
	char	*trim;
	int		i;

	if (!s || !set)
		return (NULL);
	if (find_end(s, set) == -1 || find_start(s, set) == -1)
	{
		trim = malloc(1);
		if (!trim)
			return (NULL);
		trim[0] = '\0';
		return (trim);
	}
	else
		trim = malloc((find_end(s, set) - find_start(s, set) + 2));
	if (trim == NULL)
		return (NULL);
	i = 0;
	while (i < find_end(s, set) - find_start(s, set) + 1)
	{
		trim[i] = s[i + find_start(s, set)];
		i++;
	}
	trim[i] = '\0';
	return (trim);
}
