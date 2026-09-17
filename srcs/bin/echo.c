/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 08:29:04 by tlebon            #+#    #+#             */
/*   Updated: 2024/11/25 20:31:13 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Iterates over str
// If the first char is not - and/or 1 of the following char is not an n
// returns false
// Otherwise returns true
static int	valid_arg(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (!str[0] || str[0] != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

// Iterates through cmd_tab: skip the valid arg like -n -nnn "-n"
// Then print the rest of cmd_tab separated with spaces
// If there was a -n arg(s) doesn't print a \n at the end
// Returns 0 on success, 1 on error 
int	exec_echo(char **cmd_tab)
{
	int	i;
	int	length;
	int	with_option;

	if (!cmd_tab)
		return (1);
	i = 1;
	while (cmd_tab[i] && valid_arg(cmd_tab[i]))
		++i;
	with_option = i;
	while (cmd_tab[i])
	{
		length = write(1, cmd_tab[i], ft_strlen(cmd_tab[i]));
		if (length < 0)
			return (1);
		if (cmd_tab[i + 1] && length > 0)
			if (write(1, " ", 1) < 0)
				return (1);
		i++;
	}
	if (with_option == 1)
		if (write(1, "\n", 1) < 0)
			return (1);
	return (0);
}
