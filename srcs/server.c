/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 21:11:42 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/06/30 17:03:23 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/server.h"

static t_connection_info	g_connection_info;

static void	initialize_connection_info()
{
	g_connection_info.client_pid = 0;
	g_connection_info.message = NULL;
	g_connection_info.bit_counter = 0;
	g_connection_info.checksum = 0;
	g_connection_info.status = IDLE;
}

static void	response_to_client(int client_pid, int status)
{
	if (status == SUCCESS)
		kill(client_pid, SIGUSR2);
	else
		kill(client_pid, SIGUSR1);
}

static void receive_header(signo)
{
	if (signo == SIGUSR2)
		g_connection_info.message_len += 1;
	g_connection_info.bit_counter++;
	// ft_printf("bit counter = %d\n", g_connection_info.bit_counter);
	if (g_connection_info.bit_counter == 32)
	{
		g_connection_info.bit_counter = 0;
		g_connection_info.message = \
			ft_calloc(g_connection_info.message_len + 1, 1);
		if (g_connection_info.message == NULL)
			exit(-1);
		g_connection_info.head_message = g_connection_info.message;
		g_connection_info.status = GET_MESSAGE;
		ft_printf("Message Len = %d\n", g_connection_info.message_len);
		usleep(DELAY);
		kill(g_connection_info.client_pid, SIGUSR2);
		return ;
	}
	g_connection_info.message_len <<= 1;
}

static void	receive_message(signo)
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

static void	receive_checksum(int signo)
{
	if (signo == SIGUSR2)
		g_connection_info.checksum += 1;
	g_connection_info.bit_counter++;
	// ft_printf("recevied checksum bit = %d\n", g_connection_info.bit_counter);
	if (g_connection_info.bit_counter == 16)
	{
		g_connection_info.status = VALIDATE;
		return ;
	}
	g_connection_info.checksum <<= 1;
}

//utils로 옮길 예정
static int	calculate_checksum(unsigned char *message)
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
	ft_printf("Data sum = %d\n", char_sum);
	return (char_sum);
}

static int	validate_message()
{
	ft_printf("Received checksum = %d\n", g_connection_info.checksum);
	if (calculate_checksum(g_connection_info.message) + \
		g_connection_info.checksum == VALID_DATA)
		return (SUCCESS);
	else
		return (ERROR);
}

static void	receive_signal(signo)
{
	// ft_printf("status = %d\n", g_connection_info.status);
	if (g_connection_info.status == GET_HEADER)
		receive_header(signo);
	else if (g_connection_info.status == GET_MESSAGE)
		receive_message(signo);
	else if (g_connection_info.status == GET_CHECKSUM)
		receive_checksum(signo);
	if (g_connection_info.status == VALIDATE)
	{
		if (validate_message())
		{
			//print_message
			ft_printf("%s", g_connection_info.message);
			usleep(DELAY);
			kill(g_connection_info.client_pid, SIGUSR2);
		}
		else
		{
			usleep(DELAY);
			kill(g_connection_info.client_pid, SIGUSR1);
		}
		free(g_connection_info.message);
		initialize_connection_info();
	}
}

static void handle_client(int signo, int client_pid)
{
	if (g_connection_info.status == IDLE)
	{
		g_connection_info.client_pid = client_pid;
		g_connection_info.status = GET_HEADER;
		usleep(DELAY);
		kill(client_pid, SIGUSR2);
	}
	else
	{
		usleep(DELAY);
		if (g_connection_info.client_pid == client_pid)
			receive_signal(signo);
		else
			kill(client_pid, SIGUSR1);
	}
}

static void	sig_handler(int signo, siginfo_t *sig_info, void *uc)
{
	if (g_connection_info.status != IDLE && \
		g_connection_info.client_pid != sig_info->si_pid)
		return ;
	// if (signo == SIGUSR1)
	// 	ft_printf("%d by %d\n", 0, sig_info->si_pid);
	// else if (signo == SIGUSR2)
	// 	ft_printf("%d by %d\n", 1, sig_info->si_pid);
	handle_client(signo, sig_info->si_pid);
	(void)uc;
}

int	main(void)
{
	struct sigaction	sig_struct;
	sigset_t			sig_mask;

	ft_printf("server PID = %d\n", getpid());
	initialize_connection_info();
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
