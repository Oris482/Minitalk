/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 21:28:37 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/07/03 21:28:39 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/server_bonus.h"

static int	validate_message(char *message)
{
	unsigned int	data_sum;

	data_sum = 0;
	while (*message)
	{
		data_sum += *message;
		while (data_sum & CARRY_CHECK)
			data_sum = (data_sum - CARRY_CHECK + 1);
		message++;
	}
	if (data_sum + g_connection_info.checksum == (unsigned int)VALID_DATA)
		return (PASS);
	else
		return (FAIL);
}

static void	receive_signal(int signo)
{
	int	response_signal;
	int	client_pid;

	if (g_connection_info.status == GET_HEADER)
		receive_header(signo);
	else if (g_connection_info.status == GET_MESSAGE)
		receive_message(signo);
	else if (g_connection_info.status == GET_CHECKSUM)
		receive_checksum(signo);
	if (g_connection_info.status == VALIDATE)
	{
		client_pid = g_connection_info.client_pid;
		if (validate_message(g_connection_info.head_message))
		{
			ft_printf("<Message>\n%s\n\n", g_connection_info.head_message);
			response_signal = SIGUSR2;
		}
		else
			response_signal = SIGUSR1;
		free(g_connection_info.head_message);
		initialize_connection_info();
		signal_with_delay(client_pid, response_signal);
	}
}

static void	handle_client(int signo, int client_pid)
{
	if (g_connection_info.status == IDLE)
	{
		g_connection_info.client_pid = client_pid;
		ft_printf("Connection Established with Client(%d)\n", \
		g_connection_info.client_pid);
		ft_printf("Receiving header...");
		g_connection_info.status = GET_HEADER;
		signal_with_delay(client_pid, SIGUSR2);
	}
	else
	{
		if (g_connection_info.client_pid == client_pid)
			receive_signal(signo);
		else
			signal_with_delay(client_pid, SIGUSR1);
	}
}

static void	sig_handler(int signo, siginfo_t *sig_info, void *uc)
{
	if (g_connection_info.status != IDLE && \
		g_connection_info.client_pid != sig_info->si_pid)
	{
		kill(sig_info->si_pid, SIGUSR1);
		return ;
	}
	handle_client(signo, sig_info->si_pid);
	(void)uc;
}

int	main(void)
{
	struct sigaction	sig_struct;
	sigset_t			sig_mask;

	sigemptyset(&sig_mask);
	sigaddset(&sig_mask, SIGUSR1);
	sigaddset(&sig_mask, SIGUSR2);
	sig_struct.sa_sigaction = sig_handler;
	sig_struct.sa_flags = SA_SIGINFO;
	sig_struct.sa_mask = sig_mask;
	if (sigaction(SIGUSR1, &sig_struct, NULL) == ERROR || \
		sigaction(SIGUSR2, &sig_struct, NULL) == ERROR)
		exit_with_props(1, "Sigaction return error!");
	initialize_connection_info();
	while (1)
	{
		pause();
	}
}
