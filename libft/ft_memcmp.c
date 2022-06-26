/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 20:38:12 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/03/16 18:55:52 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*tmp1;
	const unsigned char	*tmp2;
	size_t				idx;

	tmp1 = (const unsigned char *)s1;
	tmp2 = (const unsigned char *)s2;
	idx = 0;
	if (n != 0)
	{
		while (n > idx)
		{
			if (tmp1[idx] != tmp2[idx])
				return (tmp1[idx] - tmp2[idx]);
			idx++;
		}
	}
	return (0);
}
