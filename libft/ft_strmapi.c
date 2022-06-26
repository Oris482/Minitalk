/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:57:13 by jaesjeon          #+#    #+#             */
/*   Updated: 2021/11/22 15:17:34 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*result;
	size_t	str_len;
	size_t	idx;

	str_len = ft_strlen(s);
	result = (char *)malloc(str_len + 1);
	if (result == NULL)
		return (NULL);
	idx = 0;
	while (idx < str_len)
	{
		result[idx] = f(idx, s[idx]);
		idx++;
	}
	result[idx] = '\0';
	return (result);
}
