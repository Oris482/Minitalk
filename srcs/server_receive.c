/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_receive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 15:52:42 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/07/02 16:19:50 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/server.h"

void	receive_header(int signo)
{
	if (signo == SIGUSR2)
		g_connection_info.message_len += 1;
	g_connection_info.bit_counter++;
	if (g_connection_info.bit_counter == 32)
	{
		g_connection_info.bit_counter = 0;
		g_connection_info.message = \
			ft_calloc(g_connection_info.message_len + 1, 1);
		if (g_connection_info.message == NULL)
			exit(1);
		g_connection_info.head_message = g_connection_info.message;
		g_connection_info.status = GET_MESSAGE;
		usleep(DELAY);
		kill(g_connection_info.client_pid, SIGUSR2);
		return ;
	}
	g_connection_info.message_len <<= 1;
}

void	receive_message(int signo)
{
	if (signo == SIGUSR2)
		*g_connection_info.message += 1;
	g_connection_info.bit_counter++;
	if (g_connection_info.bit_counter == 8)
	{
		g_connection_info.bit_counter = 0;
		g_connection_info.message++;
		if (g_connection_info.message - g_connection_info.head_message == \
			g_connection_info.message_len)
			g_connection_info.status = GET_CHECKSUM;
		usleep(DELAY);
		kill(g_connection_info.client_pid, SIGUSR2);
		return ;
	}
	*g_connection_info.message <<= 1;
}

void	receive_checksum(int signo)
{
	if (signo == SIGUSR2)
		g_connection_info.checksum += 1;
	g_connection_info.bit_counter++;
	if (g_connection_info.bit_counter == 32)
	{
		g_connection_info.status = VALIDATE;
		return ;
	}
	g_connection_info.checksum <<= 1;
}
