/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:54:35 by jaesjeon          #+#    #+#             */
/*   Updated: 2021/11/22 16:16:00 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_sepptr(int n, int fd)
{
	if (n < 10)
		ft_putchar_fd(n + 48, fd);
	else
	{
		ft_sepptr(n / 10, fd);
		ft_putchar_fd((n % 10) + 48, fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		if (n == -2147483648)
		{
			ft_putstr_fd("-2147483648", fd);
			return ;
		}
		else
		{
			n *= (-1);
			ft_putchar_fd('-', fd);
		}
	}
	if (n == 0)
		ft_putchar_fd('0', fd);
	else
		ft_sepptr(n, fd);
}
