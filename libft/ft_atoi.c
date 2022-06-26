/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 21:34:30 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/03/10 13:38:33 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || \
			c == ' ')
		return (1);
	else
		return (0);
}

static long	ft_putnum(long result, const char *str)
{
	int	digit;

	digit = 0;
	while (*str > 47 && *str < 58)
	{
		result = (result << 1) + (result << 3) + (*str - 48);
		str++;
		digit++;
		if (result < 0 || digit > 19)
			return (-1);
	}
	return (result);
}

int	ft_atoi(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	result = ft_putnum(result, str);
	if (result < 0)
	{
		if (sign == 1)
			return (-1);
		return (0);
	}
	result *= sign;
	return (result);
}
