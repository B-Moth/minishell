/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberne <lberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:18:45 by lberne            #+#    #+#             */
/*   Updated: 2024/11/29 18:19:19 by lberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*ctrl + C*/
void	handle_sigint(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();
}

/*ctrl + C in heredoc*/
void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	g_heredoc_stop = 1;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(STDOUT_FILENO, "\n", 1);
}

void	signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	init_minishell(t_data *data, int ac)
{
	g_heredoc_stop = 0;
	if (ac > 1)
		printf("minishell : no arguments requiered\n");
	data->tokens = NULL;
	data->env_lst = NULL;
	data->line = NULL;
	data->ret = 0;
	data->loop = true;
	signals();
}
