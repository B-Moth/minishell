/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberne <lberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:16:13 by lberne            #+#    #+#             */
/*   Updated: 2024/12/10 16:55:29 by lberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_reset(t_data *data)
{
	free_tokens(data->tokens);
	data->tokens = NULL;
	free(data->line);
	data->line = NULL;
}

void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		if (tmp->str)
		{
			free(tmp->str);
			tmp->str = NULL;
		}
		free(tmp);
		tmp = NULL;
	}
}

void	free_env_lst(t_env *head)
{
	t_env	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		if (tmp->name)
		{
			free(tmp->name);
			tmp->name = NULL;
		}
		if (tmp->str)
		{
			free(tmp->str);
			tmp->str = NULL;
		}
		free(tmp);
		tmp = NULL;
	}
}

void	free_all(t_data	*data)
{
	if (data->tokens)
	{
		free_tokens(data->tokens);
		data->tokens = NULL;
	}
	if (data->env_lst)
	{
		free_env_lst(data->env_lst);
		data->env_lst = NULL;
	}
	if (data->env_cpy)
		ft_free_tab((void **)data->env_cpy);
	rl_clear_history();
}
