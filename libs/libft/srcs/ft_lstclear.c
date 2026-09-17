/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:54:52 by tlebon            #+#    #+#             */
/*   Updated: 2023/11/24 16:45:53 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*cursor;
	t_list	*buffer;

	if (!lst || !(*del))
		return ;
	cursor = *lst;
	while (cursor->next != NULL)
	{
		buffer = cursor;
		cursor = cursor->next;
		(*del)(buffer->content);
		free(buffer);
	}
	(*del)(cursor->content);
	free(cursor);
	*lst = NULL;
	return ;
}
