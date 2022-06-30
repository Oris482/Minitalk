/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:00:09 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/06/30 16:01:07 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	exit_with_props(int exit_code, char *error_msg)
{
	ft_printf("%s\n", error_msg);
	exit(exit_code);
}

void	calculate_checksum(char *message)
{
	int	char_sum;

	char_sum = 0;
	while (*message)
	{
		char_sum += *message;
		while (char_sum & CARRY_CHECK)
			char_sum = (char_sum - CARRY_CHECK + 1);
		message++;
	}
	g_connection_info.checksum = (~char_sum);
	ft_printf("Checksum = %d\n", g_connection_info.checksum);
	usleep(50);
}