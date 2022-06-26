/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:56:46 by jaesjeon          #+#    #+#             */
/*   Updated: 2021/11/19 17:28:53 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_cmp(const char *haystack, const char *needle)
{
	while (*needle != '\0')
	{
		if (*haystack != *needle)
			break ;
		haystack++;
		needle++;
	}
	if (*needle == '\0')
		return (1);
	else
		return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	cnt;
	size_t	len_needle;

	cnt = 0;
	len_needle = ft_strlen(needle);
	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack != '\0' && cnt < len)
	{
		if (*haystack == *needle)
		{
			if (len_needle > len - cnt)
				break ;
			else if (ft_cmp(haystack, needle))
				return ((char *)haystack);
		}
		haystack++;
		cnt++;
	}
	return (0);
}
