/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:24:50 by lberne            #+#    #+#             */
/*   Updated: 2024/12/11 17:46:36 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(t_token *tokens)
{
	t_token	*current;
	int		croco;

	current = tokens;
	croco = 0;
	while (current)
	{
		if (croco && (current->type < 6))
		{
			croco = 0;
			printf("\033[0;101msyntax error\033[0m\n");
			return (1);
		}
		croco = 0;
		if (current->type >= 1 && current->type <= 4)
			croco = 1;
		current = current->next;
		if (croco && !current)
		{
			printf("\033[0;101msyntax error\033[0m\n");
			return (1);
		}
	}
	return (0);
}

/*if the prompt is empty it must NOT be added to history*/
bool	empty_line(char *line)
{
	int	i;

	if (!line)
		return (true);
	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (i == (int)ft_strlen(line))
	{
		free(line);
		return (true);
	}
	return (false);
}

/*no quote can be unclosed EXCEPT if in two quotes*/
bool	quote_error(char *input)
{
	bool	open_quote;
	int		i;
	char	q;

	i = 0;
	open_quote = false;
	while (input[i])
	{
		if (input[i] == 34 || input[i] == 39)
		{
			if (!open_quote)
			{
				q = input[i];
				open_quote = true;
			}
			else if (input[i] == q)
				open_quote = false;
		}
		i++;
	}
	return (open_quote);
}

/*main ft, check for open quotes or pipes at the end or beginning*/
bool	error_check(t_data *data)
{
	if (quote_error(data->line) || data->line[0] == '|'
		|| data->line[ft_strlen(data->line + 1)] == '|')
	{
		ft_putstr_fd("\033[0;101mopen quote or pipe\033[0m\n", 2);
		ft_reset(data);
		return (true);
	}
	return (false);
}
