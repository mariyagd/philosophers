# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/02 09:32:51 by mdanchev          #+#    #+#              #
#    Updated: 2023/10/02 09:36:49 by mdanchev         ###   lausanne.ch        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c parser.c atoi_atol.c ft_calloc.c philo_linked_list.c

OBJS = ${SRCS:.c=.o}

NAME = philo

CC = gcc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror -g3

PTHLIB = -lpthread

SANITIZE	?= 0

ifeq ($(SANITIZE), 1)
CFLAGS += -fsanitize=thread
endif
.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${PTHLIB}

all: ${NAME}

clean:
	${RM} ${OBJS}

flean : clean
	${RM} ${NAME}

re: flean all
