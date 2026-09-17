/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:54:37 by tlebon            #+#    #+#             */
/*   Updated: 2023/11/24 16:45:31 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*cursor;

	if (!new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		(*lst)->content = new->content;
		return ;
	}
	cursor = *lst;
	while (cursor->next != NULL)
		cursor = cursor->next;
	cursor->next = new;
	return ;
}
