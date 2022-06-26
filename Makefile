# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/25 20:27:12 by jaesjeon          #+#    #+#              #
#    Updated: 2022/06/25 23:13:54 by jaesjeon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
# CFLAGS = -Wall -Wextra -Werror
RM = rm -f

#output file names
NAME_CLIENT = client
NAME_SERVER = server
NAME_CLIENT_BONUS = client_bonus
NAME_SERVER_BONUS = server_bonus

#for test
NAME_CLIENT_TEST = clienttest
NAME_SERVER_TEST = servertest

#Libft
DIR_LIBFT = ./libft
LIBFT = libft.a

#ft_printf
DIR_FT_PRINTF = ./ft_printf
FT_PRINTF = libftprintf.a

#Mandatory source
DIR_SRCS_MANDATORY = ./srcs
FILES_CLIENT = client.c
SRCS_CLIENT = $(addprefix $(DIR_SRCS_MANDATORY)/, $(FILES_CLIENT))
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)
FILES_SERVER = server.c
SRCS_SERVER = $(addprefix $(DIR_SRCS_MANDATORY)/, $(FILES_SERVER))
OBJS_SERVER = $(SRCS_SERVER:.c=.o)

#Bonus source
DIR_SRCS_BONUS = ./srcs_bonus
FILES_CLIENT_BONUS = client_bonus.c
SRCS_CLIENT_BONUS = $(addprefix $(DIR_SRCS_BONUS)/, $(FILES_CLIENT_BONUS))
OBJS_CLIENT_BONUS = $(SRCS_CLIENT_BONUS:.c=.o)
FILES_SERVER_BONUS = server_bonus.c
SRCS_SERVER_BONUS = $(addprefix $(DIR_SRCS_BONUS)/, $(FILES_SERVER_BONUS))
OBJS_SERVER_BONUS = $(SRCS_SERVER_BONUS:.c=.o)

#Headers
DIR_HEADERS = ./headers
HEADER_CLIENT = $(DIR_HEADERS)/client.h
HEADER_CLIENT_BONUS = $(DIR_HEADERS)/client_bonus.h
HEADER_SERVER = $(DIR_HEADERS)/server.h
HEADER_SERVER_BONUS = $(DIR_HEADERS)/server_bonus.h
HEADER_LIBFT = $(DIR_LIBFT)/libft.h

.PHONY: all clean fclean re bonus client_test server_test remove_test

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(HEADER_LIBFT) $(HEADER_CLIENT) $(OBJS_CLIENT)
	make bonus -C $(DIR_LIBFT)
	cp $(DIR_LIBFT)/$(LIBFT) .
	make bonus -C $(DIR_FT_PRINTF)
	cp $(DIR_FT_PRINTF)/$(FT_PRINTF) .
	$(CC) $(CFLAGS) $(SRCS_CLIENT) -I$(DIR_HEADERS) -L. -lft -lftprintf -o $(NAME_CLIENT)

$(NAME_SERVER): $(HEADER_LIBFT) $(HEADER_SERVER) $(OBJS_SERVER)
	make bonus -C $(DIR_LIBFT)
	cp $(DIR_LIBFT)/$(LIBFT) .
	make bonus -C $(DIR_FT_PRINTF)
	cp $(DIR_FT_PRINTF)/$(FT_PRINTF) .
	$(CC) $(CFLAGS) $(SRCS_SERVER) -I$(DIR_HEADERS) -L. -lft -lftprintf -o $(NAME_SERVER)

bonus: $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)

$(NAME_CLIENT_BONUS): $(HEADER_LIBFT) $(HEADER_CLIENT_BONUS) $(OBJS_CLIENT_BONUS)
	make bonus -C $(DIR_LIBFT)
	cp $(DIR_LIBFT)/$(LIBFT) .
	make bonus -C $(DIR_FT_PRINTF)
	cp $(DIR_FT_PRINTF)/$(FT_PRINTF) .
	$(CC) $(CFLAGS) $(SRCS_CLIENT_BONUS) -I$(DIR_HEADERS) -L. -lft -o $(NAME_CLIENT_BONUS)

$(NAME_SERVER_BONUS): $(HEADER_LIBFT) $(HEADER_SERVER_BONUS) $(OBJS_SERVER_BONUS)
	make bonus -C $(DIR_LIBFT)
	cp $(DIR_LIBFT)/$(LIBFT) .
	make bonus -C $(DIR_FT_PRINTF)
	cp $(DIR_FT_PRINTF)/$(FT_PRINTF) .
	$(CC) $(CFLAGS) $(SRCS_SERVER_BONUS) -I$(DIR_HEADERS) -L. -lft -o $(NAME_SERVER_BONUS)

clean:
	make clean -C $(DIR_LIBFT)
	make clean -C $(DIR_FT_PRINTF)
	$(RM) $(OBJS_CLIENT) $(OBJS_SERVER) $(OBJS_CLIENT_BONUS) $(OBJS_SERVER_BONUS)

fclean: clean
	$(RM) $(LIBFT) $(FT_PRINTF)
	$(RM) $(NAME_CLIENT) $(NAME_SERVER) $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)

re:
	make fclean
	make all

#for test
client_test: $(NAME_CLIENT_TEST)

server_test: $(NAME_SERVER_TEST)

remove_test:
	$(RM) $(NAME_CLIENT_TEST) $(NAME_SERVER_TEST)

$(NAME_CLIENT_TEST): $(OBJS_CLIENT) $(HEADER_CLIENT)
	make bonus -C $(DIR_LIBFT)
	cp $(DIR_LIBFT)/$(LIBFT) .
	make bonus -C $(DIR_FT_PRINTF)
	cp $(DIR_FT_PRINTF)/$(FT_PRINTF) .
	$(CC) $(SRCS_CLIENT) -I$(DIR_HEADERS) -L. -lft -lftprintf -o $(NAME_CLIENT_TEST)
	
$(NAME_SERVER_TEST): $(OBJS_SERVER) $(HEADER_SERVER)
	make bonus -C $(DIR_LIBFT)
	cp $(DIR_LIBFT)/$(LIBFT) .
	make bonus -C $(DIR_FT_PRINTF)
	cp $(DIR_FT_PRINTF)/$(FT_PRINTF) .
	$(CC) $(SRCS_SERVER) -I$(DIR_HEADERS) -L. -lft -lftprintf -o $(NAME_SERVER_TEST)
