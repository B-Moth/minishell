/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:02:56 by tlebon            #+#    #+#             */
/*   Updated: 2024/12/11 17:46:08 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Used in update_env_tab function
// Uses ft_strjoin to concatenate name, =, and str in result
// Returns a string "name=str" on succes, NULL on error
static char	*create_full_string(t_env *s_env)
{
	char	*name_prep;
	char	*result;

	if (!s_env)
		return (NULL);
	name_prep = ft_strjoin(s_env->name, "=");
	if (!name_prep)
		return (NULL);
	result = NULL;
	if (s_env->str)
		result = ft_strjoin(name_prep, s_env->str);
	if (!result)
	{
		free(name_prep);
		return (NULL);
	}
	free(name_prep);
	return (result);
}

// Used in update_env_tab
// Creates correct strings from s_env to put them in env tab 
// via create_full_string
// Returns 0 on succes, > 0 on error
static int	fill_up_env_tab(t_env *s_env, char ***env_pt)
{
	int		size;
	t_env	*curs;

	if (!s_env || !(*env_pt))
		return (1);
	curs = s_env;
	size = 0;
	while (curs)
	{
		(*env_pt)[size++] = create_full_string(curs);
		if (!(*env_pt)[size - 1])
		{
			ft_free_tab((void **)*env_pt);
			return (2);
		}
		curs = curs->next;
	}
	(*env_pt)[size] = NULL;
	return (0);
}

// Creates a new environment tab according to s_env
// If do free is enabled, free the tab pointed to by env_pt first
// Iterates through s_env to get its size and mallocs the correct size
// Via create_full_string, creates the correct string and assigns it to tab
// Tab is null terminated
// Returns 0 on succes, > 0 on error
int	update_env_tab(t_env *s_env, char ***env_pt, int do_free)
{
	t_env	*curs;
	int		size;

	if (!s_env)
		return (1);
	if (do_free)
		ft_free_tab((void **)*env_pt);
	curs = s_env;
	size = 0;
	while (curs)
	{
		size++;
		curs = curs->next;
	}
	*env_pt = malloc((size + 1) * sizeof(char *));
	if (!(*env_pt))
		return (2);
	if (fill_up_env_tab(s_env, env_pt) != 0)
		return (3);
	return (0);
}

static int	append_non_existant(t_env **env_lst, char *name, char *value,
								char *val)
{
	t_env	*var;

	if (ft_strncmp(value, "=", 1) != 0)
		var = create_env(name, "", false);
	else
		var = create_env(name, val, true);
	if (!var)
		return (1);
	append_env_lst(env_lst, var);
	return (0);
}

// Appends a new node to env_lst if there is no "name" named node inside it
// If there is a "name" named node, change its value (str) to value
// Push the modifications of env_lst to env_tab with update_env_tab function
int	update_env(t_env **env_lst, char *name, char *value, char ***env_pt)
{
	t_env	*var;
	char	*val;

	val = ft_substr(value, 1, ft_strlen(value));
	if (!val)
		return (1);
	if (already_exists(*env_lst, name) && ft_strncmp(value, "=", 1) == 0)
	{
		var = find_variable(name, *env_lst);
		free(var->str);
		var->str = ft_strdup(val);
		var->printed = true;
	}
	else if (!already_exists(*env_lst, name))
	{
		if (append_non_existant(env_lst, name, value, val) != 0)
		{
			free(val);
			return (1);
		}
	}
	free(val);
	if (update_env_tab(*env_lst, env_pt, 1) != 0)
		return (1);
	return (0);
}
