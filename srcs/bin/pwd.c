/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:34:52 by tlebon            #+#    #+#             */
/*   Updated: 2024/12/11 17:43:04 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Check si il y a des subtilitees :
// Avec le comportement de pwd dans bash pour adapter le comportement 
// Dans bash, si $PWD est unset : la cmd pwd marche quand meme
// Avec getcwd notamment avec les parametres (leaks ? error management ?)
// Uses getcwd to get working directory then prints it
int	exec_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("pwd: error retrieving current directory: getcwd");
		return (1);
	}
	printf("%s\n", path);
	free(path);
	return (0);
}
