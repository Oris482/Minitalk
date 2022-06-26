# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/11 14:33:20 by jaesjeon          #+#    #+#              #
#    Updated: 2021/12/02 21:14:59 by jaesjeon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -I.
NAME = libft.a
AR = ar
ARFLAGS = -rcus
SRCDIR = .
OBJDIR = .
SRCS = ft_memset.c	\
		ft_bzero.c	\
		ft_memcpy.c	\
		ft_memmove.c	\
		ft_memchr.c	\
		ft_memcmp.c	\
		ft_strlen.c	\
		ft_isalpha.c	\
		ft_isdigit.c	\
		ft_isalnum.c	\
		ft_isascii.c	\
		ft_isprint.c	\
		ft_toupper.c	\
		ft_tolower.c	\
		ft_strchr.c	\
		ft_strrchr.c	\
		ft_strncmp.c	\
		ft_strlcpy.c	\
		ft_strlcat.c	\
		ft_strnstr.c	\
		ft_atoi.c	\
		ft_calloc.c	\
		ft_strdup.c	\
		ft_substr.c	\
		ft_strjoin.c	\
		ft_strtrim.c	\
		ft_split.c	\
		ft_itoa.c	\
		ft_strmapi.c	\
		ft_striteri.c	\
		ft_putchar_fd.c	\
		ft_putstr_fd.c	\
		ft_putendl_fd.c	\
		ft_putnbr_fd.c
SRCS_BONUS = ft_lstnew.c	\
			 ft_lstadd_front.c	\
			 ft_lstsize.c	\
			 ft_lstlast.c	\
			 ft_lstadd_back.c	\
			 ft_lstdelone.c	\
			 ft_lstclear.c	\
			 ft_lstiter.c	\
			 ft_lstmap.c
_OBJS = $(SRCS:.c=.o)
_OBJS_BONUS = $(SRCS_BONUS:.c=.o)
OBJS = $(addprefix $(OBJDIR)/, $(_OBJS))
OBJS_BONUS = $(addprefix $(OBJDIR)/, $(_OBJS_BONUS))

ifdef WITH_BONUS
	OBJS += $(OBJS_BONUS)
endif

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c libft.h

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus:
	@make WITH_BONUS=1 all
