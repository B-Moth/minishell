/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:36:10 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/30 23:01:13 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Returns the first node of s_env that has a name equal to name
// Returns NULL on error or if no name names node is found
t_env	*find_variable(char *name, t_env *s_env)
{
	t_env	*curs;
	int		longest;

	if (!s_env || !name)
		return (NULL);
	curs = s_env;
	while (curs)
	{
		if (ft_strlen(name) > ft_strlen(curs->name))
			longest = ft_strlen(name);
		else
			longest = ft_strlen(curs->name);
		if (ft_strncmp(curs->name, name, longest) == 0)
			return (curs);
		curs = curs->next;
	}
	return (NULL);
}

// Creates and return a copy of s_env
// Returns NULL on error
t_env	*copy_s_env(t_env *s_env)
{
	t_env	*cpy;
	t_env	*curs;
	t_env	*new_s_env;

	if (!s_env)
		return (NULL);
	cpy = create_env(s_env->name, s_env->str, s_env->printed);
	if (!cpy)
		return (NULL);
	curs = s_env->next;
	while (curs)
	{
		new_s_env = create_env(curs->name, curs->str, curs->printed);
		if (!new_s_env)
		{
			free_env_lst(cpy);
			return (NULL);
		}
		append_env_lst(&cpy, new_s_env);
		curs = curs->next;
	}
	return (cpy);
}

// Iterates through s_env and checks whether an env named name exists
// Returns 1 if it exists
// Returns 0 otherwise
int	already_exists(t_env *s_env, char *name)
{
	t_env	*curs;
	int		longest;

	curs = s_env;
	while (curs)
	{
		if (ft_strlen(curs->name) > ft_strlen(name))
			longest = ft_strlen(curs->name);
		else
			longest = ft_strlen(name);
		if (ft_strncmp(curs->name, name, longest) == 0)
			return (1);
		curs = curs->next;
	}
	return (0);
}

// Returns the value (s_env->str) of the first name named node encountered
// Returns NULL on error or if no name named node is found 
char	*get_env_str(t_env *s_env, char *name)
{
	t_env	*curs;

	if (!s_env || !name)
		return (NULL);
	curs = s_env;
	while (curs)
	{
		if (ft_strncmp(name, curs->name,
				ft_strlen(name) + ft_strlen(curs->name)) == 0)
			return (curs->str);
		curs = curs->next;
	}
	return (NULL);
}

// Updates the value (s_env->str) of the first name named node encountered
// If the value is != NULL, frees it before assigning str
// Returns 0 on succes, 1 on error
int	set_env_str(t_env **s_env, char *name, char *str)
{
	t_env	*curs;

	if (!s_env || !name || !str)
		return (1);
	curs = *s_env;
	while (curs)
	{
		if (ft_strncmp(name, curs->name,
				ft_strlen(name) + ft_strlen(curs->name)) == 0)
			break ;
		curs = curs->next;
	}
	if (curs->str)
		free(curs->str);
	curs->str = str;
	return (0);
}
