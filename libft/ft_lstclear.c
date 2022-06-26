/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:00:58 by jaesjeon          #+#    #+#             */
/*   Updated: 2021/11/27 19:24:26 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*temp;

	current = *lst;
	if (*lst == NULL || del == NULL)
		return ;
	while (current->next != NULL)
	{
		temp = current->next;
		ft_lstdelone(current, del);
		current = temp;
	}
	ft_lstdelone(current, del);
	*lst = NULL;
}
