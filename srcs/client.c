/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 21:11:39 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/06/26 23:30:57 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/client.h"

static t_connection_info	g_connection_info;

void	exit_with_props(int exit_code, char *error_msg)
{
	ft_printf("%s\n", error_msg);
	exit(exit_code);
}

void	validate_pid(int pid)
{
	if (pid > 99999 || pid < -99999)
		exit_with_props(-1, "Invalid PID. Please check again!");
	else if ((pid > 0 && pid < 101) || (pid > -101 && pid < -1))
		exit_with_props(-1, "This is system PID!");
	else if (pid == 0)
		exit_with_props(-1, "This is PID for client group!");
	else if (pid == -1)
		ft_printf("%s\n", "Send signals to every 
		processes according to your authority");
	else if (pid < -100)
		ft_printf("%s\n", "Send signals to all processes 
		that are in the same group as the target PID");
	ft_printf("%s\n", "Valid PID");
}

void	sig_handler(int signo, siginfo_t *sig_info, void *uc)
{
	int	recent_signo;

	if (g_connection_info.server_pid == 0)
	{
		g_connection_info.server_pid = sig_info->si_pid;
	}
	if (g_connection_info.server_pid == sig_info->si_pid)
	{
		if (g_connection_info.prev_signo == 0)
			recent_signo = SIGUSR1;
		else
			recent_signo = SIGUSR2;
		ft_printf(" %d\n", signo);
		if (signo != recent_signo)
			exit_with_props(-1, "Connection Error!");
	}
}

void	send_signal(int pid, char *message)
{
	int		masking_bit;
	char	cur_char;

	while (*message)
	{
		masking_bit = 0b10000000;
		cur_char = *message;
		while (1)
		{
			g_connection_info.prev_signo = cur_char & masking_bit;
			ft_printf("masking bit = %d cur_char = %d\n", masking_bit, cur_char);
			ft_printf("%d", g_connection_info.prev_signo);
			usleep(50);
			if (g_connection_info.prev_signo)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			pause();
			masking_bit >>= 1;
			if (masking_bit == 0)
				break;
		}
		write(1, "\n", 1);
		message++;
	}
}

int	main(int argc, char *argv[])
{
	struct sigaction	sig_struct;
	sigset_t			sig_mask;
	size_t				message_len;

	sigemptyset(&sig_mask);
	sigaddset(&sig_mask, SIGUSR1);
	sigaddset(&sig_mask, SIGUSR2);
	sig_struct.sa_sigaction = sig_handler;
	sig_struct.sa_mask = sig_mask;
	sig_struct.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sig_struct, NULL);
	sigaction(SIGUSR2, &sig_struct, NULL);
	if (argc == 3)
	{
		validate_pid(ft_atoi(argv[1]));
		send_signal(ft_atoi(argv[1]), argv[2]);
	}
	else
		exit_with_props(-1, "Arguments error! #Usage : ./filename PID Message");
	ft_printf("%s\n", "Successful exit");
	return (0);
}
