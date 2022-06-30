/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 21:12:29 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/06/30 16:55:39 by jaesjeon         ###   ########.fr       */
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

# define IDLE 0
# define GET_HEADER 1
# define GET_MESSAGE 2
# define GET_CHECKSUM 3
# define VALIDATE 4

# define DELAY 70
# define RETRY_MAX 5

# define CARRY_CHECK 65536
# define VALID_DATA -1

typedef struct s_connection_info {
	int	client_pid;
	int	message_len;
	unsigned char	*message;
	unsigned char	*head_message;
	int	checksum;
	unsigned char	bit_counter;
	int	status;
}	t_connection_info;
#endif