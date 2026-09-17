/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:55:31 by tlebon            #+#    #+#             */
/*   Updated: 2023/11/24 16:47:35 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*cursor;

	if (!lst)
		return (0);
	size = 1;
	cursor = lst;
	while (cursor->next != NULL)
	{
		size++;
		cursor = cursor->next;
	}
	return (size);
}
