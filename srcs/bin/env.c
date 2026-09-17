/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:28:47 by tlebon            #+#    #+#             */
/*   Updated: 2024/11/18 15:38:24 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Prints env with a \n inbetween each string
int	exec_env(t_env *s_env)
{
	t_env	*curs;

	if (!s_env)
		return (125);
	curs = s_env;
	while (curs)
	{
		if (curs->printed)
			printf("%s=%s\n", curs->name, curs->str);
		curs = curs->next;
	}	
	return (0);
}
