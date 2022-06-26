/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 12:05:26 by jaesjeon          #+#    #+#             */
/*   Updated: 2021/11/20 16:57:53 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*joined;
	size_t	idx;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	joined = (char *)malloc(s1_len + s2_len + 1);
	if (joined == NULL)
		return (NULL);
	idx = 0;
	while (s1_len > 0)
	{
		joined[idx++] = *s1++;
		s1_len--;
	}
	while (s2_len > 0)
	{
		joined[idx++] = *s2++;
		s2_len--;
	}
	joined[idx] = '\0';
	return (joined);
}
