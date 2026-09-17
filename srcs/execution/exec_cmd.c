/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:22:46 by tlebon            #+#    #+#             */
/*   Updated: 2024/12/11 17:37:43 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_err_msg(char *name, char *error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(error, 2);
}

int	check_permissions(char *path)
{
	struct stat	buf;

	if (access(path, F_OK) != 0)
	{
		print_err_msg(path, ": No such file or directory\n");
		return (127);
	}
	if (stat(path, &buf) != 0)
		return (perror("Stat failed"), -1);
	if (S_ISDIR(buf.st_mode))
	{
		print_err_msg(path, ": Is a directory\n");
		return (126);
	}
	if (access(path, X_OK) != 0)
	{
		print_err_msg(path, ": Permission denied\n");
		return (126);
	}
	return (0);
}

// Is executed by child process of exec_cmd
// Search for path of the cmd via get_cmd_path
// Close fdin and fdout if they are != of STDIN or STDOUT
// Execute the cmd via execve
// AJOUTER DES TRUCS SI EXECVE FAIL
static int	execute(t_manager *s_manager, t_data *s_data)
{
	char	*path;
	char	**cmd_tab;
	int		check;

	if (!s_manager || !s_data)
		return (1);
	cmd_tab = prepare_cmd_tab(s_manager->s_exec->cmd_block);
	if (!cmd_tab)
		return (clean_up(s_data, s_manager, NULL, NULL), 0);
	path = get_cmd_path(s_data->env_lst, cmd_tab[0]);
	if (!path)
	{
		print_err_msg(cmd_tab[0], ": command not found\n");
		return (clean_up(s_data, s_manager, cmd_tab, NULL), 127);
	}
	check = check_permissions(path);
	if (check != 0)
		return (clean_up(s_data, s_manager, cmd_tab, path), check);
	if (execve(path, cmd_tab, s_manager->s_exec->env_tab) != 0)
		perror("Execve failed");
	return (clean_up(s_data, s_manager, cmd_tab, path), 127);
}

// Creates a new process via fork
// Child process redirects STDIN and STDOUT to fdin and fdout then execute cmd
// Parent process only returns id of child process
// Returns -1 on error
int	exec_cmd(t_manager *s_manager, t_data *s_data)
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
		else if (redirect_input(fdin, fdout) != 0)
			clean_child(s_data, s_manager);
		close_child(s_manager);
		close_remain_hd(s_manager->hd_tab);
		exit(execute(s_manager, s_data));
	}
	return (id);
}

// Used to go to a new cycle of execution
// Searches for a pipe in s_token list
// If there is one, move the head of s_token list to the token after the pipe
// Closes writing end of the current pipe and update rd_pipe to the reading end
// of the current pipe
// If no pipe is found, s_token will be set to NULL and the exec loop will stop
void	continue_exec(t_token **s_token, t_manager *s_manager)
{
	if (s_manager->prev_pipe && s_manager->pipefd)
	{
		if (close(s_manager->prev_pipe[0]) != 0)
			perror("Close failed");
		free(s_manager->prev_pipe);
	}
	if (s_manager->pipefd)
	{
		s_manager->prev_pipe = s_manager->pipefd;
		if (close(s_manager->pipefd[1]) != 0)
			perror("Close failed");
		s_manager->pipefd = NULL;
	}
	*s_token = search_next_token(*s_token, PIPE);
	if (*s_token)
		*s_token = (*s_token)->next;
}
