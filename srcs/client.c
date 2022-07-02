/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 21:11:39 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/07/02 20:35:13 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/client.h"

static t_connection_info	g_connection_info;

static void	sig_handler(int signo, siginfo_t *sig_info, void *uc)
{
	if (g_connection_info.status == IDLE)
		g_connection_info.server_pid = sig_info->si_pid;
	if (g_connection_info.server_pid == sig_info->si_pid)
	{
		if (g_connection_info.status == IDLE && signo == SIGUSR2)
		{
			ft_printf("%s\n", "Connection Established!");
			g_connection_info.status = SEND_HEADER;
		}
		else if (g_connection_info.status == VALIDATE)
		{
			if (signo == SIGUSR2)
				exit_with_props(0, " <<< Success!");
			else
				exit_with_props(1, " <<< Data sending error!");
		}
		else
		{
			if (signo == SIGUSR1)
				exit_with_props(1, "\nError response from server");
		}
	}
	(void)uc;
}

static void	send_header(int pid)
{
	unsigned int	masking_bit;

	masking_bit = 1 << 31;
	g_connection_info.status = IDLE;
	signal_with_delay(pid, SIGUSR2);
	pause();
	ft_printf("%s %d", "Sending header...", g_connection_info.message_len);
	while (1)
	{
		if (g_connection_info.message_len & masking_bit)
			signal_with_delay(g_connection_info.server_pid, SIGUSR2);
		else
			signal_with_delay(g_connection_info.server_pid, SIGUSR1);
		masking_bit >>= 1;
		if (masking_bit == 0)
			break ;
	}
	ft_printf("%s", " >>> Waiting response...");
	pause();
	ft_printf("%s", " <<< OK!\n");
	g_connection_info.send_progress = 0;
	g_connection_info.status = SEND_MESSAGE;
}

static void	send_message(char *message)
{
	unsigned int	masking_bit;
	char			*head_message;
	int				cur_progress;

	head_message = message;
	cur_progress = 0;
	ft_printf("Sending message ");
	while (*message)
	{
		masking_bit = 1 << 7;
		while (masking_bit != 0)
		{
			if (*message & masking_bit)
				signal_with_delay(g_connection_info.server_pid, SIGUSR2);
			else
				signal_with_delay(g_connection_info.server_pid, SIGUSR1);
			masking_bit >>= 1;
		}
		message++;
		print_send_progress(&cur_progress, head_message, \
			message, g_connection_info.message_len);
	}
	pause();
	ft_printf("%s", " <<< OK!\n");
	g_connection_info.status = SEND_CHECKSUM;
}

static void	send_checksum(void)
{
	unsigned int		masking_bit;

	masking_bit = 1 << 31;
	ft_printf("%s %u", "Sending checksum...", g_connection_info.checksum);
	while (1)
	{
		if (g_connection_info.checksum & masking_bit)
			signal_with_delay(g_connection_info.server_pid, SIGUSR2);
		else
			signal_with_delay(g_connection_info.server_pid, SIGUSR1);
		masking_bit >>= 1;
		if (masking_bit == 0)
			break ;
	}
	ft_printf("%s", " >>> Waiting response...");
	g_connection_info.status = VALIDATE;
	pause();
}

int	main(int argc, char *argv[])
{
	struct sigaction	sig_struct;
	sigset_t			sig_mask;
	int					pid;

	sigemptyset(&sig_mask);
	sigaddset(&sig_mask, SIGUSR1);
	sigaddset(&sig_mask, SIGUSR2);
	sig_struct.sa_sigaction = sig_handler;
	sig_struct.sa_mask = sig_mask;
	sig_struct.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sig_struct, NULL) == ERROR || \
		sigaction(SIGUSR2, &sig_struct, NULL) == ERROR)
		exit_with_props(1, "Sigaction return error!");
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		validate_argument(pid, argv[2]);
		g_connection_info.message_len = ft_strlen(argv[2]);
		g_connection_info.checksum = calculate_checksum(argv[2]);
		send_header(pid);
		send_message(argv[2]);
		send_checksum();
	}
	exit_with_props(1, "Arguments error! #Usage : ./filename PID Message");
}
