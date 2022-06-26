/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 12:22:30 by jaesjeon          #+#    #+#             */
/*   Updated: 2021/11/24 21:12:56 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_wordcnt(char const *s, char c)
{
	unsigned int	word_cnt;

	word_cnt = 0;
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		while (*s != c && *s != '\0')
			s++;
		if (*(s - 1) != c)
			word_cnt++;
	}
	return (word_cnt);
}

static void	*ft_arrfree(char **splited, unsigned int list_idx)
{
	unsigned int	idx;

	idx = 0;
	while (idx < list_idx)
		free(splited[idx++]);
	free(splited);
	return (NULL);
}

static void	ft_putstr(char const *s, unsigned int save_p, \
		unsigned int idx, char *splited)
{
	while (save_p < idx)
		*splited++ = s[save_p++];
	*splited = '\0';
}

char	**ft_split(char const *s, char c)
{
	char			**splited;
	unsigned int	str_idx;
	unsigned int	list_idx;
	unsigned int	save_p;
	unsigned int	word_cnt;

	word_cnt = ft_wordcnt(s, c);
	splited = (char **)ft_calloc((word_cnt + 1), sizeof(char *));
	if (splited == NULL)
		return (NULL);
	str_idx = 0;
	list_idx = 0;
	while (s[str_idx] != '\0' && list_idx < word_cnt)
	{
		while (s[str_idx] == c)
			str_idx++;
		save_p = str_idx;
		while (s[str_idx] != c && s[str_idx] != '\0')
			str_idx++;
		splited[list_idx] = (char *)malloc(str_idx - save_p + 1);
		if (splited[list_idx] == NULL)
			return (ft_arrfree(splited, list_idx));
		ft_putstr(s, save_p, str_idx, splited[list_idx++]);
	}
	return (splited);
}
