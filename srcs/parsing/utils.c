/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberne <lberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:53:26 by lberne            #+#    #+#             */
/*   Updated: 2024/11/22 17:06:00 by lberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_special(const char *c, int char_len)
{
	return (char_len == 1 && (c[0] == '|' || c[0] == '<' || c[0] == '>'));
}

bool	is_quote(const char *c, int char_len)
{
	return (char_len == 1 && (c[0] == '"' || c[0] == '\''));
}

bool	is_wspace(const char *c, int char_len)
{
	if (char_len == 1 && (c[0] <= 32 || c[0] == 127))
		return (true);
	if (char_len == 2 && (unsigned char)c[0] == 0xC2
		&& (unsigned char)c[1] == 0xA0)
		return (true);
	return (false);
}

bool	match(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (false);
	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
		i++;
	if (!s1[i] && !s2[i])
		return (true);
	return (false);
}

void	ft_cat(char *dest, const char *src, const char c_src)
{
	int		i;
	int		j;

	if (!dest)
		return ;
	j = ft_strlen(dest);
	if (!c_src && src)
	{
		i = 0;
		while (src[i])
		{
			dest[j] = src[i];
			i++;
			j++;
		}
	}
	else if (!src && c_src)
	{
		dest[j] = c_src;
		j++;
	}
	dest[j] = '\0';
}
