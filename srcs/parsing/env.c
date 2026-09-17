/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:55:37 by lberne            #+#    #+#             */
/*   Updated: 2024/12/11 17:38:21 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*return str associated with the env name if it exist, NULL otherwise*/
char	*env_extractor(char *name, t_env *env_lst)
{
	t_env	*current;

	current = env_lst;
	while (current)
	{
		if (match(name, current->name))
			return (current->str);
		current = current->next;
	}
	return (NULL);
}

/*return the next env after "start" by getting his name and use env_extractor*/
char	*get_env(char *token, int start, t_env *env_lst)
{
	char	*name;
	char	*res;
	int		i;

	if (!token)
		return (NULL);
	name = (char *)malloc(sizeof(unsigned char) * ft_strlen(token) + 18);
	if (!name)
		return (NULL);
	name[0] = '\0';
	i = 0;
	if (token[start] == '$')
		ft_cat(name, "SYSTEMD_EXEC_PID", 0);
	else
	{
		while (ft_isalnum(token[start]) || token[start] == '_')
			name[i++] = token[start++];
		name[i++] = '\0';
	}
	res = ft_strdup(env_extractor(name, env_lst));
	return (free(name), res);
}

/*create a nod of the env_lst*/
t_env	*create_env(char *name, char *str, bool printed)
{
	t_env	*new_env;

	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
	{
		perror("Failed memory allocation in create_env");
		return (NULL);
	}
	new_env->name = ft_strdup(name);
	new_env->str = ft_strdup(str);
	new_env->printed = printed;
	new_env->ret = 0;
	new_env->prev = NULL;
	new_env->next = NULL;
	return (new_env);
}

/*link a nod to the env_lst*/
void	append_env_lst(t_env **head, t_env *new_env)
{
	t_env	*last;

	if (!*head)
		*head = new_env;
	else
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_env;
		new_env->prev = last;
	}
}

/*main ft of the env_lst creator, work by spliting each line of env by '='*/
int	create_env_lst(char **v_env, t_data *data)
{
	char	**temp_env;
	char	*name;
	char	*str;

	while (*v_env)
	{
		temp_env = ft_split(*v_env, '=');
		if (!temp_env)
			return (0);
		name = ft_strdup(temp_env[0]);
		if (temp_env[1])
			str = handle_copy_env(temp_env[1], name);
		else
			str = ft_strdup("");
		if (!name || !str)
			return (0);
		append_env_lst(&data->env_lst, create_env(name, str, true));
		ft_free_tab((void **)temp_env);
		free(name);
		free(str);
		v_env++;
	}
	return (1);
}
