/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 11:40:20 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/03/07 19:11:02 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t		cnt;
	size_t		idx;

	cnt = ft_strlen(src);
	idx = 1;
	while (*src != '\0' && idx++ < dstsize)
	{
		*dst = *src;
		dst++;
		src++;
	}
	if (dstsize != 0)
		*dst = '\0';
	return (cnt);
}
