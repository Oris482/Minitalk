/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 21:12:29 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/06/27 22:50:41 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"

# define SUCCESS 0
# define ERROR -1
# define DELAY 50
# define RETRY_MAX 5
# define CARRY_CHECK 65536
# define VALID_DATA 65535

typedef struct s_connection_info {
	int	client_pid;
	int	message_len;
	int data_byte;
	int	data_sum;
	int	bit_counter;
	int	status;
}	t_connection_info;
#endif