/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 20:42:37 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/03/16 18:55:14 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*tmp_dst;
	const unsigned char	*tmp_src;

	if (dst == NULL && src == NULL)
		return (NULL);
	tmp_dst = (unsigned char *)dst;
	tmp_src = (const unsigned char *)src;
	while (n-- > 0)
		*tmp_dst++ = *tmp_src++;
	return (dst);
}
