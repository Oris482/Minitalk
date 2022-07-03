/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_receive_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 15:52:42 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/07/03 21:28:47 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/server_bonus.h"

void	receive_header(int signo)
{
	if (signo == SIGUSR2)
		g_connection_info.message_len |= \
			(1U << (31 - g_connection_info.bit_counter));
	g_connection_info.bit_counter++;
	if (g_connection_info.bit_counter == 32)
	{
		g_connection_info.bit_counter = 0;
		g_connection_info.message = \
			ft_calloc(g_connection_info.message_len + 1, 1);
		if (g_connection_info.message == NULL)
			exit(1);
		g_connection_info.head_message = g_connection_info.message;
		ft_printf(" <<< %d\n", g_connection_info.message_len);
		ft_printf("Receiving message...");
		g_connection_info.status = GET_MESSAGE;
		signal_with_delay(g_connection_info.client_pid, SIGUSR2);
		return ;
	}
}

void	receive_message(int signo)
{
	if (signo == SIGUSR2)
		*g_connection_info.message |= \
			(1U << (7 - g_connection_info.bit_counter));
	g_connection_info.bit_counter++;
	if (g_connection_info.bit_counter == 8)
	{
		g_connection_info.bit_counter = 0;
		g_connection_info.message++;
		if (g_connection_info.message - g_connection_info.head_message == \
			g_connection_info.message_len)
		{
			ft_printf(" Finished!\n");
			ft_printf("Receiving checksum...");
			g_connection_info.status = GET_CHECKSUM;
			signal_with_delay(g_connection_info.client_pid, SIGUSR2);
		}
		return ;
	}
}

void	receive_checksum(int signo)
{
	if (signo == SIGUSR2)
		g_connection_info.checksum |= \
			(1U << (31 - g_connection_info.bit_counter));
	g_connection_info.bit_counter++;
	if (g_connection_info.bit_counter == 32)
	{
		ft_printf(" <<< %u\n", g_connection_info.checksum);
		g_connection_info.status = VALIDATE;
		return ;
	}
}
