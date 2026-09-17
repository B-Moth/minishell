/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:41:55 by tlebon            #+#    #+#             */
/*   Updated: 2024/12/11 17:44:29 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Supposed to redirect the prev and next pointers of neighbours and free 
// everything inside the node and the node
// As ret is stored in the first node of the list, if we want to free the first
// node, we need to transfert the value of ret to the next node and make the 
// s_env pointer points to the new first node
void	free_env_node(t_env *node, t_env **s_env)
{
	if (!*s_env || !node)
		return ;
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	if (node == *s_env && node->next)
	{
		node->next->ret = node->ret;
		*s_env = node->next;
	}
	if (node == *s_env && !node->next)
	{
		*s_env = NULL;
	}
	free(node->name);
	free(node->str);
	free(node);
	return ;
}

// Checks for each arg of cmd_tab if is variable exists
// If it does, deletes it, if it doesn't does nothing
// Updates env when the deletions have been made inside s_env
// Returns 0 on success and 1 on error
int	exec_unset(char **cmd_tab, t_env **s_env, char ***env)
{
	int		i;
	t_env	*var;

	if (!cmd_tab || !*s_env)
		return (1);
	i = 1;
	while (cmd_tab[i])
	{
		var = find_variable(cmd_tab[i], *s_env);
		if (var != NULL)
			free_env_node(var, s_env);
		i++;
	}
	return (update_env_tab(*s_env, env, 1));
}
