/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:19:51 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/03/10 13:41:12 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	idx;

	idx = 0;
	while (s[idx] != '\0')
	{
		f(idx, s + idx);
		idx++;
	}
}
