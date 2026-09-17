/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finishes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:28:19 by lberne            #+#    #+#             */
/*   Updated: 2024/12/11 17:46:50 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*replace the $*/
int	handle_dollars(char *str, char *new_str, int start, t_data data)
{
	char	*env;

	start++;
	if (!ft_isalnum(str[start]) && str[start] != '$' && str[start] != '?')
	{
		if (solo_dollar(str, start))
			ft_cat(new_str, NULL, '$');
	}
	else if (str[start] == '?' )
	{
		handle_dollar_question_mark(new_str, data);
		start++;
	}
	else
	{
		env = get_env(str, start, data.env_lst);
		if (env)
		{
			ft_cat(new_str, env, 0);
			free(env);
		}
		start = get_endof_envname(str, start);
	}
	return (start);
}

/*get rid of quotes the proper way ('' or "")*/
int	handle_quotes(char *str, char *new_str, int start, t_data data)
{
	if (str[start] == 39)
	{
		start++;
		while (str[start] != 39)
		{
			ft_cat(new_str, NULL, str[start]);
			start++;
		}
	}
	else if (str[start] == 34)
	{
		start++;
		while (str[start] != 34)
		{
			if (str[start] == '$')
				start = handle_dollars(str, new_str, start, data);
			else
			{
				ft_cat(new_str, NULL, str[start]);
				start++;
			}
		}
	}
	new_str[ft_strlen(new_str)] = '\0';
	return (start + 1);
}

int	handle_clean(char *str, char *new_str, int start, t_data data)
{
	int	i;

	i = ft_strlen(new_str);
	if (!str || !new_str || !data.env_lst)
		return (0);
	if (!is_quote(&str[start], utf8_char_len(str[start])) && str[start] != '$')
	{
		while (str[start] && !is_quote(&str[start], utf8_char_len(str[start]))
			&& str[start] != '$')
		{
			new_str[i] = str[start];
			i++;
			start++;
		}
		new_str[i] = '\0';
	}
	else if (is_quote(&str[start], utf8_char_len(str[start])))
		start = handle_quotes(str, new_str, start, data);
	else if (str[start] == '$')
		start = handle_dollars(str, new_str, start, data);
	return (start);
}

/*finishes handle quotes and $ replacements by replacing old str
by a fully interpreted token, hello there is a flag that indicate that either
a quote or a $ has been found during parsing*/
int	finishes(t_token *tokens, t_data data)
{
	t_token	*current_token;
	char	*new_str;
	int		new_len;
	int		i;

	current_token = tokens;
	while (current_token)
	{
		if (current_token->hello_there == true)
		{
			new_len = token_len(current_token->str, data.env_lst);
			new_str = (char *)malloc(sizeof(unsigned char) * (new_len + 1));
			if (!new_str)
				return (1);
			new_str[0] = '\0';
			i = 0;
			while (current_token->str[i])
				i = handle_clean(current_token->str, new_str, i, data);
			new_str[ft_strlen(new_str)] = '\0';
			free(current_token->str);
			current_token->str = new_str;
		}
		current_token = current_token->next;
	}
	return (0);
}
