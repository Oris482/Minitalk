/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 21:11:42 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/06/28 22:41:54 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/server.h"

static t_connection_info	g_connection_info;

static void	response_to_client(int client_pid, int status)
{
	if (status == SUCCESS)
		kill(client_pid, SIGUSR2);
	else
		kill(client_pid, SIGUSR1);
}

static void	sig_handler(int signo, siginfo_t *sig_info, void *uc)
{
	int	a = 0;

	if (g_connection_info.client_pid == 0)
	{
		g_connection_info.client_pid = sig_info->si_pid;
	}
	// if (g_connection_info.client_pid == sig_info->si_pid)
	if (sig_info->si_pid != 0)
	{
		ft_printf("%d ", a);
		g_connection_info.data_byte <<= 1;
		if (signo == SIGUSR2)
			g_connection_info.data_byte += 1;
		g_connection_info.bit_counter++;
		a++;
		if (g_connection_info.bit_counter == 8)
		{
			g_connection_info.data_sum += g_connection_info.data_byte;
			// ft_printf("%c", g_connection_info.data_byte);
			// write(1, &g_connection_info.data_byte, 1);
			g_connection_info.bit_counter = 0;
			g_connection_info.data_byte = 0;
		}
		// usleep(50);
		// kill(g_connection_info.client_pid, signo);
		// ft_printf("%d\n", g_connection_info.data_byte);
	}
}

int	main(void)
{
	struct sigaction	sig_struct;
	sigset_t			sig_mask;

	ft_printf("server PID = %d\n", getpid());
	g_connection_info.client_pid = 0;
	g_connection_info.status = 0;
	g_connection_info.data_sum = 0;
	g_connection_info.data_byte = 0;
	g_connection_info.bit_counter = 0;
	sigemptyset(&sig_mask);
	sigaddset(&sig_mask, SIGUSR1);
	sigaddset(&sig_mask, SIGUSR2);
	sig_struct.sa_sigaction = sig_handler;
	sig_struct.sa_flags = SA_SIGINFO;
	sig_struct.sa_mask = sig_mask;
	sigaction(SIGUSR1, &sig_struct, NULL);
	sigaction(SIGUSR2, &sig_struct, NULL);
	while (1)
	{
		pause();
	}
}
