/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberne <lberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:39:07 by lberne            #+#    #+#             */
/*   Updated: 2024/11/22 17:11:50 by lberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_len(char *token, t_env *env_lst)
{
	size_t	res;
	int		i;
	char	*env;

	if (!token)
		return (0);
	res = ft_strlen(token);
	i = 0;
	while (token[i])
	{
		if (token[i] == '$')
		{
			env = get_env(token, i + 1, env_lst);
			if (env)
			{
				res += ft_strlen(env);
				free(env);
			}
			if (token[i + 1] == '?')
				res += 3;
		}
		i++;
	}
	return (res);
}

t_token	*create_token(const char *str, int type)
{
	int		i;
	t_token	*new_token;

	i = 0;
	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->str = ft_strdup(str);
	if (!new_token->str)
	{
		free(new_token);
		return (NULL);
	}
	new_token->type = type;
	new_token->hello_there = false;
	while (str[i])
	{
		if (is_quote(&str[i], utf8_char_len(str[i])) || str[i] == '$')
			new_token->hello_there = true;
		i++;
	}
	new_token->prev = NULL;
	new_token->next = NULL;
	return (new_token);
}

void	append_token(t_token **head, t_token *new_token)
{
	t_token	*last;

	if (!*head)
		*head = new_token;
	else
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_token;
		new_token->prev = last;
	}
}
