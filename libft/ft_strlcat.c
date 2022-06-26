/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 11:55:59 by jaesjeon          #+#    #+#             */
/*   Updated: 2021/11/19 16:47:42 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	idx;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize < dst_len + 1)
		return (src_len + dstsize);
	idx = 0;
	while (*dst != '\0')
	{
		idx++;
		dst++;
	}
	while (*src != '\0' && idx++ < dstsize - 1)
		*dst++ = *src++;
	*dst = '\0';
	return (dst_len + src_len);
}
