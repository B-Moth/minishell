/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:15:30 by tlebon            #+#    #+#             */
/*   Updated: 2024/12/11 14:12:59 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tab_size(char **tab)
{
	int	i;

	if (!tab)
		return (0);
	i = 0;
	while (tab[i])
		i++;
	return (i);
}

// Iterates s_token from start (s_token) to a pipe token or end of list
// Returns a pointer to the first cmd token found
// Returns NULL if no CMD token is found when the loop stops
t_token	*search_next_cmd(t_token *s_token)
{
	t_token	*curs;

	curs = s_token;
	while (curs && !is_type(curs, PIPE))
	{
		if (is_type(curs, CMD))
			return (curs);
		curs = curs->next;
	}
	return (NULL);
}

// Iterates through s_token until it finds a token of type type
// If it founds one, return a pointer to that token
// If the iteration went until the end of the list returns NULL
t_token	*search_next_token(t_token *s_token, int type)
{
	t_token	*curs;

	if (!s_token)
		return (NULL);
	curs = s_token;
	while (curs)
	{
		if (is_type(curs, type))
			return (curs);
		curs = curs->next;
	}
	return (NULL);
}

// Checks for existence and readability of the infile in argument
// If it exists and is readable, opens it and returns the fd
// Returns -1 on failure
int	open_infile(char *file_path)
{
	int	fd;

	if (!file_path)
		return (-1);
	if (!access(file_path, F_OK) && !access(file_path, R_OK))
	{
		fd = open(file_path, O_RDONLY);
		if (fd == -1)
		{
			perror("Open failed");
			return (-1);
		}
	}
	else
	{
		perror("Access failed");
		return (-1);
	}
	return (fd);
}

// Checks if the outfile in argument exists and is writable
// If it doesn't exist, or if it exists and is writable
// Opens it and returns the fd
// Uses O_APPEND Flag when append bool is set up to 1
// Return -1 on failure
int	open_outfile(char *file_path, int append)
{
	int	fd;

	if (!file_path)
		return (-1);
	if (access(file_path, F_OK) == -1)
		fd = open(file_path, O_WRONLY | O_CREAT, 0644);
	else
	{
		if (access(file_path, W_OK) == -1)
		{
			perror("Access failed");
			return (-1);
		}
		else if (append == 1)
			fd = open(file_path, O_WRONLY | O_APPEND);
		else
			fd = open(file_path, O_WRONLY | O_TRUNC);
	}
	if (fd == -1)
		perror("Open failed");
	return (fd);
}
