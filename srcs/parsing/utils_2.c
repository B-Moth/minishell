/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberne <lberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:21:18 by lucas             #+#    #+#             */
/*   Updated: 2024/11/29 18:16:41 by lberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*return the number of bytes the char is coded with
(needed to handle non-ascii char)*/
int	utf8_char_len(unsigned char c)
{
	if ((c & 0x80) == 0)
		return (1);
	if ((c & 0xE0) == 0xC0)
		return (2);
	if ((c & 0xF0) == 0xE0)
		return (3);
	if ((c & 0xF8) == 0xF0)
		return (4);
	return (1);
}

char	*iterate_shlvl(char *str)
{
	int		temp;
	char	*res;

	res = NULL;
	temp = ft_atoi(str);
	temp++;
	res = ft_itoa(temp);
	return (res);
}

char	*handle_copy_env(char *env, char *name)
{
	if (match(name, "SHLVL"))
		return (iterate_shlvl(env));
	else
		return (ft_strdup(env));
}
