/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 21:11:42 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/06/26 23:18:25 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/server.h"

static t_connection_info	g_connection_info;

void	response_to_client(int client_pid, int status)
{
	if (status == SUCCESS)
		kill(client_pid, SIGUSR2);
	else
		kill(client_pid, SIGUSR1);
}

void	sig_handler(int signo, siginfo_t *sig_info, void *uc)
{
	if (g_connection_info.client_pid == 0)
	{
		g_connection_info.client_pid = sig_info->si_pid;
	}
	// if (g_connection_info.client_pid == sig_info->si_pid)
	if (sig_info->si_pid != 0)
	{
		ft_printf("Client PID = %d, %d\n", sig_info->si_pid, signo);
		usleep(50);
		kill(g_connection_info.client_pid, signo);
	}
}

int	main(void)
{
	struct sigaction	sig_struct;
	sigset_t			sig_mask;

	ft_printf("server PID = %d\n", getpid());
	g_connection_info.client_pid = 0;
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
