/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 21:12:26 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/06/27 22:58:08 by jaesjeon         ###   ########.fr       */
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
# define DELAY 50
# define RETRY_MAX 5
// # define CARRY_CHECK 65536
# define CARRY_CHECK 128
# define VALID_DATA 65535
typedef struct s_connection_info {
	int	server_pid;
	int	message_len;
	int	recent_signo;
	int	checksum;
	int	status;
}	t_connection_info;
#endif