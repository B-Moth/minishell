/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 23:44:07 by tlebon            #+#    #+#             */
/*   Updated: 2024/12/11 17:44:14 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	select_bin(char **cmd_tab, t_data *s_data)
{
	int	ret;

	ret = 1;
	if (ft_strncmp(cmd_tab[0], "echo", ft_strlen(cmd_tab[0])) == 0)
		ret = exec_echo(cmd_tab);
	else if (ft_strncmp(cmd_tab[0], "cd", ft_strlen(cmd_tab[0])) == 0)
		ret = exec_cd(cmd_tab, &s_data->env_lst, &s_data->env_cpy);
	else if (ft_strncmp(cmd_tab[0], "pwd", ft_strlen(cmd_tab[0])) == 0)
		ret = exec_pwd();
	else if (ft_strncmp(cmd_tab[0], "export", ft_strlen(cmd_tab[0])) == 0)
		ret = exec_export(cmd_tab, &s_data->env_lst, &s_data->env_cpy);
	else if (ft_strncmp(cmd_tab[0], "unset", ft_strlen(cmd_tab[0])) == 0)
		ret = exec_unset(cmd_tab, &s_data->env_lst, &s_data->env_cpy);
	else if (ft_strncmp(cmd_tab[0], "env", ft_strlen(cmd_tab[0])) == 0)
		ret = exec_env(s_data->env_lst);
	else if (ft_strncmp(cmd_tab[0], "exit", ft_strlen(cmd_tab[0])) == 0)
		ret = exec_exit(cmd_tab, s_data);
	return (ret);
}

// Is executed by child process of exec_builtin
// Compare the cmd of cmd_tab (cmd_tab[0]) and launch the correct builtin
// Returns > 0 on error or builtin values
// static int	execute_builtin(t_exec *s_exec, t_env **s_env, char ***env_pt)
static int	execute_builtin(t_manager *s_manager, t_data *s_data, bool children)
{
	char	**cmd_tab;
	int		ret;

	if (!s_manager->s_exec || !s_data)
		return (1);
	cmd_tab = prepare_cmd_tab(s_manager->s_exec->cmd_block);
	if (!cmd_tab)
		return (2);
	ret = select_bin(cmd_tab, s_data);
	ft_free_tab((void **)cmd_tab);
	if (children)
	{
		free_s_manager(s_manager, true);
		free_all(s_data);
	}
	return (ret);
}

// Used when builtin belongs to a pipeline and therefore need to be forked
// Forks then redirects in/output and launch bin function in the child process
// Returns the ID of the child process or -1 on error
// static int	exec_builtin_pipeline(t_manager *s_manager,
// 									t_env **s_env, char ***env_pt)
static int	exec_builtin_pipeline(t_manager *s_manager, t_data *s_data)
{
	int	id;
	int	fdin;
	int	fdout;

	fdin = -2;
	fdout = -2;
	if (!s_manager || !s_data || !s_data->env_lst || !s_data->env_cpy)
		return (-1);
	id = fork();
	if (id == -1)
		return (perror("Fork failed"), -1);
	if (id == 0)
	{
		if (s_manager->pipefd)
			if (close(s_manager->pipefd[0]) != 0)
				perror("Close failed");
		if (set_fd_in_out(&fdin, &fdout, s_manager) != 0)
			clean_child(s_data, s_manager);
		if (redirect_input(fdin, fdout) != 0)
			clean_child(s_data, s_manager);
		close_child(s_manager);
		close_remain_hd(s_manager->hd_tab);
		exit(execute_builtin(s_manager, s_data, true));
	}
	return (id);
}

// Used when builtin doesn't belong to a pipeline
// Redirects the in/output correctly then launch the corresponding
// bin function with exec_builtin then redirects the in/output to basic state
static int	exec_basic_bin(t_manager *s_manager, t_data *s_data)
{
	int	saved_stdin;
	int	saved_stdout;
	int	fdin;
	int	fdout;
	int	ret;

	fdin = -2;
	fdout = -2;
	if (set_fd_in_out(&fdin, &fdout, s_manager) != 0)
		return (1);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (redirect_input(fdin, fdout) != 0)
	{
		ft_putstr_fd("Redirect input error :\n", 2);
		return (2);
	}
	ret = execute_builtin(s_manager, s_data, false);
	if (redirect_input(saved_stdin, saved_stdout) != 0)
	{
		ft_putstr_fd("Redirection to STDIN STDOUT failed\n", 2);
		return (3);
	}
	return (ret);
}

// Checks if the builtin to be executed belongs to a pipeline
// If it is, launch exec_builtin_pipeline function
// Otherwise launch exec_basic_bin
// int	exec_builtin(t_manager *s_manager, t_env **s_env, char ***env_pt)
int	exec_builtin(t_manager *s_manager, t_data *s_data)
{
	if (!s_manager || !s_data || !s_data->env_lst || !s_data->env_cpy)
		return (1);
	if (search_next_token(s_manager->s_exec->cmd_block, PIPE) != NULL
		|| is_type(s_manager->s_exec->cmd_block->prev, PIPE))
		return (exec_builtin_pipeline(s_manager, s_data));
	return (exec_basic_bin(s_manager, s_data));
}
