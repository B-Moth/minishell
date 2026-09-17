/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:55:59 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/14 18:55:54 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// CHECKED
// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	size_t	i;
// 	char	*substr;

// 	if (!s)
// 		return (NULL);
// 	if (start >= ft_strlen(s))
// 		return (ft_strdup(""));
// 	else if (start + len > ft_strlen(s))
// 		i = ft_strlen(s) - start + 1;
// 	else
// 		i = len + 1;
// 	substr = malloc(i * sizeof(char));
// 	if (substr == NULL)
// 		return (NULL);
// 	i = start;
// 	while (i - start < len && s[i])
// 	{
// 		substr[i - start] = s[i];
// 		i++;
// 	}
// 	substr[i - start] = '\0';
// 	return (substr);
// }

// Use ft_strjoin on s1 and s2 then free them before returning the joined string
char	*lucas_safe(char *s1, char *s2)
{
	char	*lucas;

	lucas = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	if (!lucas)
		return (NULL);
	return (lucas);
}
// CHECKED
// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*join;
// 	size_t	i;
// 	size_t	len1;
// 	size_t	len2;

// 	len1 = ft_strlen(s1);
// 	len2 = ft_strlen(s2);
// 	if (!s1 || !s2)
// 		return (NULL);
// 	i = 0;
// 	join = malloc((len1 + len2 + 1) * sizeof(char));
// 	if (join == NULL)
// 		return (NULL);
// 	while (i < len1)
// 	{
// 		join[i] = s1[i];
// 		i++;
// 	}
// 	while (i < len1 + len2)
// 	{
// 		join[i] = s2[i - len1];
// 		i++;
// 	}
// 	join[i] = '\0';
// 	return (join);
// }
// CHECKED
// size_t	ft_strlen(const char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		i++;
// 	}
// 	return (i);
// }
// CHECKED
// char	*ft_strdup(const char *s)
// {
// 	int		i;
// 	char	*dup;

// 	i = 0;
// 	dup = malloc((ft_strlen(s) + 1));
// 	if (dup == NULL)
// 		return (NULL);
// 	while (s[i])
// 	{
// 		dup[i] = s[i];
// 		i++;
// 	}
// 	dup[i] = '\0';
// 	return (dup);
// }
