/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:23:57 by tlebon            #+#    #+#             */
/*   Updated: 2024/12/10 19:57:40 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Utilise dans execute pour tout free 
void	clean_up(t_data *s_data, t_manager *s_manager, char **cmd_tab,
		char *path)
{
	free_s_manager(s_manager, true);
	free_all(s_data);
	if (cmd_tab)
		ft_free_tab((void **)cmd_tab);
	if (path)
		free(path);
}

void	close_child(t_manager *s_manager)
{
	if (s_manager->pipefd)
	{
		clean_close(s_manager->pipefd[0]);
		clean_close(s_manager->pipefd[1]);
	}
	if (s_manager->prev_pipe)
	{
		clean_close(s_manager->prev_pipe[0]);
		clean_close(s_manager->prev_pipe[1]);
	}
}

void	clean_child(t_data *s_data, t_manager *s_manager)
{
	close_child(s_manager);
	free_s_manager(s_manager, true);
	free_all(s_data);
	exit (1);
}

int	close_hd_tab_fd(int	**tab)
{
	int			i;
	struct stat	info;

	if (!tab)
		return (1);
	i = 0;
	while (tab[i])
	{
		if (fstat(tab[i][0], &info) == 0)
		{
			if (close(tab[i][0]) != 0)
				perror("Close failed");
		}
		i++;
	}
	ft_free_tab((void **)tab);
	return (0);
}

void	free_s_manager(t_manager *s_manager, bool error)
{
	if (!s_manager)
		return ;
	if (s_manager->hd_tab)
		if (close_hd_tab_fd(s_manager->hd_tab) != 0)
			ft_putstr_fd("Close error in close_hd_tab_fd function", 2);
	if (s_manager->pipefd)
		free(s_manager->pipefd);
	if (error)
		if (s_manager->prev_pipe)
			free(s_manager->prev_pipe);
	if (s_manager->s_exec)
		free(s_manager->s_exec);
	free(s_manager);
}
