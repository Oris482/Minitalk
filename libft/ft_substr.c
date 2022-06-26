/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:56:16 by jaesjeon          #+#    #+#             */
/*   Updated: 2021/11/27 17:50:56 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	str_len;
	size_t	idx;

	str_len = ft_strlen(s);
	if ((str_len - start) < len && str_len > start)
		len = str_len - start;
	else if (str_len <= start)
		len = 0;
	sub = (char *)malloc(len + 1);
	if (sub == NULL)
		return (NULL);
	if (start >= str_len)
	{
		*sub = '\0';
		return (sub);
	}
	idx = 0;
	while (s[start] != '\0' && len > 0)
	{
		sub[idx++] = s[start++];
		len--;
	}
	sub[idx] = '\0';
	return (sub);
}
