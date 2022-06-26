/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 10:14:03 by jaesjeon          #+#    #+#             */
/*   Updated: 2021/11/19 11:46:12 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*zero_mem;

	zero_mem = malloc(count * size);
	if (zero_mem == NULL)
		return (NULL);
	ft_bzero(zero_mem, (count * size));
	return (zero_mem);
}
