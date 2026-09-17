/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:55:06 by tlebon            #+#    #+#             */
/*   Updated: 2023/11/24 16:46:36 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*cursor;

	if (!lst || !(*f))
		return ;
	cursor = lst;
	while (cursor->next != NULL)
	{
		(*f)(cursor->content);
		cursor = cursor->next;
	}
	(*f)(cursor->content);
	return ;
}
