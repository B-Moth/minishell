/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:55:52 by tlebon            #+#    #+#             */
/*   Updated: 2024/12/11 16:53:58 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Creates a pipe and write inside with get_next_line on STDIN
// When the delimiter is encountered, input is freed, the writing end of the
// pipe is closed and a pointer to the pipe is returned
// Returns NULL on error
void	sig_set(void)
{
	struct sigaction	old_sigint;
	struct sigaction	sa;

	sa.sa_handler = heredoc_sigint_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, &old_sigint);
	g_heredoc_stop = 0;
}

static int	*writing_loop(char *delimiter, int *new_pipe)
{
	char	*input;

	ft_putstr(">");
	input = get_next_line(STDIN_FILENO);
	while (input)
	{
		if (g_heredoc_stop)
			break ;
		if (ft_strlen(input) == ft_strlen(delimiter) + 1
			&& ft_strncmp(delimiter, input, ft_strlen(delimiter)) == 0)
		{
			free(input);
			if (close(new_pipe[1]) != 0)
				perror("Close failed");
			new_pipe[1] = -1;
			return (new_pipe);
		}
		write(new_pipe[1], input, ft_strlen(input));
		free(input);
		ft_putstr(">");
		input = get_next_line(STDIN_FILENO);
	}
	if (close(new_pipe[1]) != 0 || close(new_pipe[0]) != 0)
		perror("Close failed");
	return (free(input), free(new_pipe), NULL);
}

static int	*write_new_hd_pipe(char *delimiter)
{
	int		*new_pipe;

	sig_set();
	if (!delimiter)
		return (NULL);
	new_pipe = malloc(2 * sizeof(int));
	if (!new_pipe)
		return (NULL);
	if (pipe(new_pipe) != 0)
	{
		perror("Pipe failed");
		return (NULL);
	}
	return (writing_loop(delimiter, new_pipe));
}

// Iterates on the cmd prompt pointed to by s_token and counts the number
// of heredoc
// Mallocs a tab with the correct number of pipes needed and fills them 
// Returns NULL on error
int	**new_hd_tab(t_token *s_token)
{
	t_token	*curs;
	int		**hd_pipes_tab;
	int		size;

	if (allocate_hd_tab(s_token, &hd_pipes_tab) != 0)
		return (NULL);
	curs = s_token;
	size = 0;
	while (curs)
	{
		if (is_type(curs, HEREDOC) && curs->next && is_type(curs->next, ARG))
		{
			hd_pipes_tab[size] = write_new_hd_pipe(curs->next->str);
			if (!hd_pipes_tab[size])
			{
				close_hd_tab_fd(hd_pipes_tab);
				return (NULL);
			}
			++size;
		}
		curs = curs->next;
	}
	if (hd_pipes_tab)
		hd_pipes_tab[size] = NULL;
	return (hd_pipes_tab);
}
