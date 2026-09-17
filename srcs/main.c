/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:39:13 by tlebon            #+#    #+#             */
/*   Updated: 2024/12/11 17:49:43 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	g_heredoc_stop = false;

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)av;
	init_minishell(&data, ac);
	if (!create_env_lst(env, &data))
		return (free_all(&data), -1);
	if (update_env_tab(data.env_lst, &data.env_cpy, 0) != 0)
		return (data.ret = 1, 1);
	while (data.loop)
	{
		data.line = readline("\033[1;94mminishell>\033[0m ");
		if (!data.line)
			break ;
		if (empty_line(data.line))
			continue ;
		add_history(data.line);
		if (error_check(&data))
			continue ;
		if (let_me_cook(&data) != 0)
			break ;
		data.ret = launch_exec(&data);
		ft_reset(&data);
	}
	return (free_all(&data), printf("exit\n"), data.ret);
}
