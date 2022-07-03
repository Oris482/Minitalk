/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 21:12:29 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/07/03 21:23:57 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"

# define PASS 1
# define FAIL 0

# define IDLE 0
# define GET_HEADER 1
# define GET_MESSAGE 2
# define GET_CHECKSUM 3
# define VALIDATE 4

# define DELAY 10

# define CARRY_CHECK 65536
# define VALID_DATA -1

void	initialize_connection_info(void);
void	exit_with_props(int exit_code, char *error_msg);
void	signal_with_delay(int pid, int signo);
void	receive_header(int signo);
void	receive_message(int signo);
void	receive_checksum(int signo);

typedef struct s_connection_info {
	int				client_pid;
	int				message_len;
	char			*message;
	char			*head_message;
	unsigned int	checksum;
	char			bit_counter;
	int				status;
}	t_connection_info;

t_connection_info	g_connection_info;

#endif