/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 15:19:19 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/07/02 16:41:21 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/client.h"

void	exit_with_props(int exit_code, char *error_msg)
{
	ft_printf("%s\n", error_msg);
	exit(exit_code);
}

void	signal_with_delay(int pid, int signo)
{
	usleep(DELAY);
	kill(pid, signo);
}

void	validate_argument(int pid, char *message)
{
	if (pid > 99999 || pid < -99999)
		exit_with_props(1, "Invalid PID. Please check again!");
	else if ((pid > 0 && pid < 101) || (pid > -101 && pid < -1))
		exit_with_props(1, "This is system PID!");
	else if (pid == 0)
		exit_with_props(1, "This is PID for client group!");
	else if (pid == -1)
		exit_with_props(1, "Send signals to every processes \
		according to your authority - BLOCKED");
	else if (pid < -100)
		ft_printf("%s\n", "Send signals to all processes \
		that are in the same group as the target PID");
	ft_printf("%s\n", "Valid PID");
	if (ft_strlen(message) == 0)
		exit_with_props(-1, "Empty message!");
}

unsigned int	calculate_checksum(char *message)
{
	unsigned int	char_sum;

	char_sum = 0;
	while (*message)
	{
		char_sum += *message;
		while (char_sum & CARRY_CHECK)
			char_sum = (char_sum - CARRY_CHECK + 1);
		message++;
	}
	return (~char_sum);
}
