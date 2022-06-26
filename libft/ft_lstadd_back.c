/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:37:29 by jaesjeon          #+#    #+#             */
/*   Updated: 2021/11/27 19:25:01 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*back;

	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		new->next = NULL;
		return ;
	}
	back = ft_lstlast(*lst);
	back->next = new;
}
