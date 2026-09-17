/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 13:14:16 by tlebon            #+#    #+#             */
/*   Updated: 2024/11/28 23:57:51 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Used to assign to fdin the correct fd
// If curs is of type R_IN or HEREDOC, and the following token is type ARG
// Open_infile tries to open the following token and assigns it to fdin
// Errors on open_infile are handled in set_fd_in_out function
static void	handle_fdin(t_token *curs, int *fdin, t_manager *s_manager)
{
	if (is_type(curs, R_IN) && curs->next && is_type(curs->next, ARG))
	{
		if (*fdin > 2)
			if (close(*fdin) != 0)
				perror("Close failed");
		*fdin = open_infile(curs->next->str);
	}	
	else if (is_type(curs, HEREDOC) && curs->next
		&& is_type(curs->next, ARG))
	{
		if (*fdin > 2)
			if (close(*fdin) != 0)
				perror("Close failed");
		*fdin = chose_hd_fd(s_manager->hd_tab);
	}
}

// Used to assign to fdout the correct fd
// If curs is of type R_OUT or R_OUT_APPEND, and the following token is type ARG
// Open_outfile tries to open the following token and assigns it to fdout
// Errors on open_outfile are handled in set_fd_in_out function
static void	handle_fdout(t_token *curs, int *fdout)
{
	if (is_type(curs, R_OUT) && curs->next && is_type(curs->next, ARG))
	{
		if (*fdout > 2)
			if (close(*fdout) != 0)
				perror("Close failed");
		*fdout = open_outfile(curs->next->str, 0);
	}
	else if (is_type(curs, R_OUT_APPEND) && curs->next
		&& is_type(curs->next, ARG))
	{
		if (*fdout > 2)
			if (close(*fdout) != 0)
				perror("Close failed");
		*fdout = open_outfile(curs->next->str, 1);
	}	
}

// If *fdin / *fdout is still = to -2, it means that no redirection operators
// nor heredoc has been found on the cmd block
// This function checks if the cmd block is after a pipe or before a pipe and
// redirects fdin and fdout to the correct fd
static void	handle_pipeline(t_token *curs, t_manager *s_manager,
							int *fdin, int *fdout)
{
	if (*fdin == -2)
	{
		if (s_manager->s_exec->cmd_block->prev
			&& is_type(s_manager->s_exec->cmd_block->prev, PIPE))
			*fdin = s_manager->prev_pipe[0];
		else
			*fdin = STDIN_FILENO;
	}
	if (*fdout == -2)
	{
		if (curs && is_type(curs, PIPE))
			*fdout = s_manager->pipefd[1];
		else
			*fdout = STDOUT_FILENO;
	}	
}

// Iterates on the prompt until its end or a token PIPE
// For each redirection operators encountered, opens the corresponding
// file and assigns its fd to fdin/out after closing their precedent fd
// (if it exists)
// If no redirection operator is encountered but there is a PIPE token before
// or after cmd block, assign the correct READ/WRITE entry of pipefd to
// fdin/fdout
// Otherwise, assigns STDIN/OUT to fdin/out
int	set_fd_in_out(int *fdin, int *fdout, t_manager *s_manager)
{
	t_token	*curs;

	if (!s_manager)
		return (1);
	curs = s_manager->s_exec->cmd_block;
	while (curs && !is_type(curs, PIPE))
	{
		handle_fdin(curs, fdin, s_manager);
		handle_fdout(curs, fdout);
		curs = curs->next;
		if (*fdin == -1 || *fdout == -1)
		{
			clean_close(*fdin);
			clean_close(*fdout);
			return (1);
		}
	}
	handle_pipeline(curs, s_manager, fdin, fdout);
	return (0);
}

// Redirect STDIN and STDOUT to fdin and fdout
// Close fdin and fdout after redirection
// If stin/out is STDIN/OUT the redirection does nothing more but fdin(STDIN)
// for ex is not closed
int	redirect_input(int fdin, int fdout)
{
	if (dup2(fdin, STDIN_FILENO) == -1)
	{
		perror("Dup2 failed");
		return (1);
	}
	if (dup2(fdout, STDOUT_FILENO) == -1)
	{
		perror("Dup2 failed");
		return (2);
	}
	if (fdin != STDIN_FILENO)
		if (close(fdin) != 0)
			perror("Close failed");
	if (fdout != STDOUT_FILENO)
		if (close(fdout) != 0)
			perror("Close failed");
	return (0);
}
