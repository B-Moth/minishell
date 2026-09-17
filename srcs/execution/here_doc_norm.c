/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_norm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:12:52 by tlebon            #+#    #+#             */
/*   Updated: 2024/12/11 17:46:23 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	allocate_hd_tab(t_token *s_token, int ***hd_pipes_tab)
{
	t_token	*curs;
	int		size;

	if (!s_token)
		return (1);
	size = 0;
	curs = s_token;
	while (curs)
	{
		if (is_type(curs, HEREDOC) && curs->next && is_type(curs->next, ARG))
			size++;
		curs = curs->next;
	}
	if (size == 0)
	{
		*hd_pipes_tab = NULL;
		return (0);
	}
	*hd_pipes_tab = malloc((size + 1) * sizeof(int *));
	if (!hd_pipes_tab)
		return (1);
	(*hd_pipes_tab)[size] = NULL;
	return (0);
}

int	chose_hd_fd(int **hd_pipes_tab)
{
	int	i;

	if (!hd_pipes_tab)
		return (-1);
	i = 0;
	while (hd_pipes_tab[i])
	{
		if (hd_pipes_tab[i][1] < -1)
			i++;
		else
		{
			hd_pipes_tab[i][1] = -3;
			if (i > 0 && hd_pipes_tab[i - 1][1] == -3)
				hd_pipes_tab[i - 1][1] = -2;
			return (hd_pipes_tab[i][0]);
		}
	}
	return (-1);
}

static void	hd_update(int ***hd_tab)
{
	int	i;

	i = 0;
	while ((*hd_tab)[i])
	{
		if ((*hd_tab)[i][1] > -2)
		{
			(*hd_tab)[i][1] = -2;
			if (close((*hd_tab)[i][0]) != 0)
				perror("Close failed hd");
			break ;
		}
		i++;
	}
}

int	update_hd_tab(t_token *s_token, int ***hd_tab)
{
	t_token	*curs;

	if (!s_token || !(*hd_tab))
		return (1);
	curs = s_token;
	while (curs && !is_type(curs, PIPE))
	{
		if (is_type(curs, HEREDOC) && curs->next && is_type(curs->next, ARG))
			hd_update(hd_tab);
		curs = curs->next;
	}
	return (0);
}

void	close_remain_hd(int **hd_pipes_tab)
{
	int			i;

	if (!hd_pipes_tab)
		return ;
	i = 0;
	while (hd_pipes_tab[i])
	{
		if (hd_pipes_tab[i][1] == -1)
			clean_close(hd_pipes_tab[i][0]);
		i++;
	}
}
