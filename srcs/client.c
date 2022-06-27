/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 21:11:39 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/06/27 23:01:02 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/client.h"

static t_connection_info	g_connection_info;

static void	exit_with_props(int exit_code, char *error_msg)
{
	ft_printf("%s\n", error_msg);
	exit(exit_code);
}

static void	validate_pid(int pid)
{
	if (pid > 99999 || pid < -99999)
		exit_with_props(-1, "Invalid PID. Please check again!");
	else if ((pid > 0 && pid < 101) || (pid > -101 && pid < -1))
		exit_with_props(-1, "This is system PID!");
	else if (pid == 0)
		exit_with_props(-1, "This is PID for client group!");
	else if (pid == -1)
		ft_printf("%s\n", "Send signals to every processes \
		according to your authority");
	else if (pid < -100)
		ft_printf("%s\n", "Send signals to all processes \
		that are in the same group as the target PID");
	ft_printf("%s\n", "Valid PID");
}

static void	sig_handler(int signo, siginfo_t *sig_info, void *uc)
{
	if (g_connection_info.recent_signo == 0)
		g_connection_info.recent_signo = signo;
	if (g_connection_info.server_pid == 0)
	{
		g_connection_info.server_pid = sig_info->si_pid;
	}
}

static void	send_signal(int pid, char *message)
{
	int		masking_bit;
	char	cur_char;

	while (*message)
	{
		masking_bit = 0b10000000;
		cur_char = *message;
		while (1)
		{
			ft_printf("masking bit = %d cur_char = %d\n", masking_bit, cur_char);
			usleep(50);
			if (cur_char & masking_bit)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			// pause();
			masking_bit >>= 1;
			if (masking_bit == 0)
				break ;
		}
		write(1, "\n", 1);
		message++;
	}
}

static void	send_checksum(int pid)
{
	int		masking_bit;

	// masking_bit = 0b1000000000000000;
	masking_bit = 0b10000000;
	while (1)
	{
		ft_printf("masking bit = %d checksum = %d\n", masking_bit, g_connection_info.checksum);
		usleep(50);
		if (g_connection_info.checksum & masking_bit)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		// pause();
		masking_bit >>= 1;
		if (masking_bit == 0)
			break ;
	}
	write(1, "\n", 1);
}

static void	calculate_checksum(char *message)
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
}

static void make_connection(int pid)
{
	g_connection_info.recent_signo = 0;
	g_connection_info.status = 0;
	kill(pid, SIGUSR2);
	pause();
	if (g_connection_info.recent_signo == SIGUSR2)
	{
		ft_printf("%s\n", "Connect Success! Start send signal...");
		g_connection_info.server_pid = pid;
		g_connection_info.status = 1;
	}
	else if (g_connection_info.recent_signo == SIGUSR1)
	{
		exit_with_props(-1, "Cannot connect with server!");
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
		calculate_checksum(argv[2]);
		// make_connection(ft_atoi(argv[1]));
		send_signal(ft_atoi(argv[1]), argv[2]);
		send_checksum(ft_atoi(argv[1]));
	}
	else
		exit_with_props(-1, "Arguments error! #Usage : ./filename PID Message");
	ft_printf("%s\n", "Successful exit");
	return (0);
}
