/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 21:12:29 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/06/26 22:08:18 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include "../ft_printf/ft_printf.h"

# define SUCCESS 0
# define ERROR -1

typedef struct s_connection_info {
	int	client_pid;
	int	prev_signo;
	int	message_len;
}	t_connection_info;