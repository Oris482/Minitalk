/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 21:11:39 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/06/30 16:58:29 by jaesjeon         ###   ########.fr       */
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
	if (g_connection_info.status == IDLE && signo == SIGUSR2)
	{
		g_connection_info.server_pid = sig_info->si_pid;
		ft_printf("%s\n", "Connect Success! Start send signal...");
		g_connection_info.status = SEND_HEADER;
		usleep(DELAY);
	}
	else if (g_connection_info.status == VALIDATE)
	{
		if (signo == SIGUSR2)
			exit_with_props(1, "Success!");
		else
			exit_with_props(-1, "Data sending error!");
	}
	else
	{
		if (signo == SIGUSR1)
			exit_with_props(-1, "Error response from server");
		else
			return ;
	}
}

static void	send_header(char *message)
{
	unsigned int	masking_bit;
	int		bit_counter;

	masking_bit = 1 << 31;
	bit_counter = 0;
	g_connection_info.message_len = ft_strlen(message);
	// ft_printf("Message Len = %d\n", g_connection_info.message_len);
	while (1)
	{
		// ft_printf("masking bit = %d\n", masking_bit);
		usleep(DELAY);
		if (g_connection_info.message_len & masking_bit)
			kill(g_connection_info.server_pid, SIGUSR2);
		else
			kill(g_connection_info.server_pid, SIGUSR1);
		masking_bit >>= 1;
		bit_counter++;
		// ft_printf("bit counter = %d\n", bit_counter);
		if (masking_bit == 0)
			break ;
	}
	pause();
	g_connection_info.status = SEND_MESSAGE;
}

static void	send_signal(char *message)
{
	int		masking_bit;
	char	cur_char;

	while (*message)
	{
		masking_bit = 1 << 7;
		cur_char = *message;
		while (1)
		{
			usleep(DELAY);
			if (cur_char & masking_bit)
				kill(g_connection_info.server_pid, SIGUSR2);
			else
				kill(g_connection_info.server_pid, SIGUSR1);
			masking_bit >>= 1;
			if (masking_bit == 0)
				break ;
		}
		pause();
		message++;
	}
	g_connection_info.status = SEND_CHECKSUM;
}

static void	send_checksum()
{
	int		masking_bit;

	masking_bit = 1 << 15;
	while (1)
	{
		usleep(DELAY);
		if (g_connection_info.checksum & masking_bit)
			kill(g_connection_info.server_pid, SIGUSR2);
		else
			kill(g_connection_info.server_pid, SIGUSR1);
		masking_bit >>= 1;
		if (masking_bit == 0)
			break ;
	}
	g_connection_info.status = VALIDATE;
	pause();
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
	usleep(DELAY);
}

static void make_connection(int pid)
{
	g_connection_info.status = IDLE;
	kill(pid, SIGUSR2);
	pause();
}

int	main(int argc, char *argv[])
{
	struct sigaction	sig_struct;
	sigset_t			sig_mask;
	size_t				message_len;
	int					pid;

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
		pid = ft_atoi(argv[1]);
		validate_pid(pid);
		calculate_checksum(argv[2]);
		make_connection(pid);
		send_header(argv[2]);
		send_signal(argv[2]);
		send_checksum();
	}
	else
		exit_with_props(-1, "Arguments error! #Usage : ./filename PID Message");
	ft_printf("%s\n", "Successful exit");
	return (0);
}
