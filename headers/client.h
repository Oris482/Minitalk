/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 21:12:26 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/07/02 16:41:30 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"

# define SUCCESS 0
# define ERROR -1

# define IDLE 0
# define SEND_HEADER 1
# define SEND_MESSAGE 2
# define SEND_CHECKSUM 3
# define VALIDATE 4

# define DELAY 500
# define CARRY_CHECK 65536

void			exit_with_props(int exit_code, char *error_msg);
void			validate_argument(int pid, char *message);
unsigned int	calculate_checksum(char *message);
void	signal_with_delay(int pid, int signo);

typedef struct s_connection_info {
	int				server_pid;
	int				message_len;
	unsigned int	checksum;
	int				status;
}	t_connection_info;

#endif