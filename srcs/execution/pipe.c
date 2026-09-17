/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:06:40 by tlebon            #+#    #+#             */
/*   Updated: 2024/12/09 17:41:11 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Iterates through s_token
// Creates a pipe if a PIPE token is encountered and assigns it to pipefd
// Assigns NULL to pipefd if no PIPE token is found when curs reaches the end
// Returns 0 if a pipe is created
// If no PIPE token is found and pipefd is assigned NULL and returns -1
// Returns > 0 on error
int	create_pipe(t_manager *s_manager, t_token *s_token)
{
	t_token	*curs;

	if (!s_manager || !s_token)
		return (1);
	curs = s_token;
	while (curs)
	{
		if (is_type(curs, PIPE))
		{
			s_manager->pipefd = malloc(2 * sizeof(int));
			if (!s_manager->pipefd)
				return (2);
			if (pipe(s_manager->pipefd) != 0)
			{
				perror("Pipe failed");
				return (3);
			}
			return (0);
		}
		curs = curs->next;
	}
	s_manager->pipefd = NULL;
	return (-1);
}

void	clean_close(int fd)
{
	struct stat	info;

	if (fstat(fd, &info) == 0)
	{
		if (close(fd) != 0)
			perror("Close failed");
	}
}
