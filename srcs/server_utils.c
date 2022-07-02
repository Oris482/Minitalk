/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 15:32:45 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/07/02 18:40:52 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/server.h"

void	initialize_connection_info(void)
{
	g_connection_info.client_pid = 0;
	g_connection_info.message_len = 0;
	g_connection_info.message = NULL;
	g_connection_info.head_message = NULL;
	g_connection_info.bit_counter = 0;
	g_connection_info.checksum = 0;
	g_connection_info.status = IDLE;
	ft_printf("Server Ready : PID = %d\n", getpid());
}

void	signal_with_delay(int pid, int signo)
{
	usleep(DELAY);
	kill(pid, signo);
}
