/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:55:12 by tlebon            #+#    #+#             */
/*   Updated: 2023/11/24 16:46:46 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*cursor;

	if (!lst)
		return (NULL);
	cursor = lst;
	while (cursor->next != NULL)
		cursor = cursor->next;
	return (cursor);
}
