/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finishes_normer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberne <lberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:32:22 by lberne            #+#    #+#             */
/*   Updated: 2024/12/11 16:46:18 by lberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	solo_dollar(char *str, int start)
{
	if (ft_isdigit(str[start]))
		return (false);
	else if (is_quote(&str[start], utf8_char_len(str[start])))
		return (false);
	else if (!is_quote(&str[start], utf8_char_len(str[start])))
		return (true);
	else if (is_quote(&str[start - 2], utf8_char_len(str[start - 2])))
		return (true);
	return (false);
}

void	handle_dollar_question_mark(char *new_str, t_data data)
{
	char	*ret;

	ret = ft_itoa(data.ret);
	if (!ret || !new_str)
		return ;
	ft_cat(new_str, ret, 0);
	free(ret);
}

/* self-explanatory */
int	get_endof_envname(char *str, int start)
{
	if (str[start] == '$' || ft_isdigit (str[start]))
		start++;
	else
	{
		while (ft_isalnum(str[start]) || str[start] == '_')
			start++;
	}
	return (start);
}
