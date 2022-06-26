/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 11:19:27 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/03/16 18:56:15 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				idx;
	const unsigned char	*tmp1;
	const unsigned char	*tmp2;

	idx = 0;
	tmp1 = (const unsigned char *)s1;
	tmp2 = (const unsigned char *)s2;
	if (n == 0)
		return (0);
	while ((*tmp1 != '\0' && *tmp2 != '\0') && *tmp1 == *tmp2 && idx < n - 1)
	{
		tmp1++;
		tmp2++;
		idx++;
	}
	return (*tmp1 - *tmp2);
}
