/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:48:41 by tlebon            #+#    #+#             */
/*   Updated: 2023/11/24 16:56:58 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*substr;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	else if (start + len > ft_strlen(s))
		i = ft_strlen(s) - start + 1;
	else
		i = len + 1;
	substr = malloc(i * sizeof(char));
	if (substr == NULL)
		return (NULL);
	i = start;
	while (i - start < len && s[i])
	{
		substr[i - start] = s[i];
		i++;
	}
	substr[i - start] = '\0';
	return (substr);
}
