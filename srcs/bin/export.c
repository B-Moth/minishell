/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:41:33 by tlebon            #+#    #+#             */
/*   Updated: 2024/12/09 16:58:16 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Check if name starts with an alphabetic char or an _ and if it contains 
// only alphanumeric chars
// Returns 1 if the conditions are fullfilled, 0 otherwise
static int	invalid_name(char *name)
{
	int	i;

	if (!name)
		return (1);
	if (!ft_isalpha(name[0]) && name[0] != '_')
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		{
			ft_putstr_fd("minishell: export: '", 2);
			ft_putstr_fd(name, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

// Checks if the string exported is valid and assigns name and value
// If var has an = char, assigns the chars after it to value and 
// the chars before to name
// If var doesn't have an = char, var is treated as a name only export
// Name is checked via invalid_name function: if invalid 1 is assigned to ret
// For the moment, if var doesn't have an = char, error is returned
// Returns 0 on succes, 1 on error
static int	assign_check_arg(char *var, char **value, char **name, int *ret)
{
	*value = ft_strchr(var, '=');
	if (!*value)
		*name = ft_strdup(var);
	else
		*name = ft_substr(var, 0, ft_strlen(var) - ft_strlen(*value));
	if (!name)
		return (1);
	if (invalid_name(*name))
	{
		*ret = 1;
		return (1);
	}
	if (!*value)
		*value = "";
	return (0);
}

static void	print_export(t_env *to_print)
{
	if (to_print->printed)
		printf("export %s=\"%s\"\n", to_print->name, to_print->str);
	else
		printf("export %s\n", to_print->name);
}

// Used when export is called w/o args
// Supposed to print all the exported variables in alphabetical order
static int	lone_export(t_env *s_env)
{
	t_env	*s_env_cpy;
	t_env	*curs;
	t_env	*printed;

	s_env_cpy = copy_s_env(s_env);
	if (!s_env_cpy)
		return (1);
	curs = s_env_cpy;
	printed = curs;
	while (curs)
	{
		while (curs)
		{
			if (ft_strncmp(curs->name, printed->name,
					ft_strlen(curs->name) + ft_strlen(printed->name)) < 0)
				printed = curs;
			curs = curs->next;
		}
		print_export(printed);
		free_env_node(printed, &s_env_cpy);
		curs = s_env_cpy;
		printed = curs;
	}
	free_env_lst(s_env_cpy);
	return (0);
}

// 
int	exec_export(char **cmd_tab, t_env **s_env, char ***env)
{
	int		i;
	int		ret;
	char	*value;
	char	*name;

	if (!cmd_tab || !*s_env || !*env)
		return (1);
	if (!cmd_tab[1])
		return (lone_export(*s_env));
	i = 1;
	ret = 0;
	while (cmd_tab[i])
	{
		if (assign_check_arg(cmd_tab[i++], &value, &name, &ret) != 0)
		{
			free(name);
			continue ;
		}
		if (update_env(s_env, name, value, env) != 0)
			return (4);
		free(name);
	}
	return (ret);
}
