# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/02 09:32:51 by mdanchev          #+#    #+#              #
#    Updated: 2023/10/05 12:11:55 by mdanchev         ###   lausanne.ch        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c parser.c atoi_atol.c ft_calloc.c philo_linked_list.c threads.c \
	   time.c life.c game.c print.c free_philo.c ft_strlen.c \
	   ft_strncmp.c min_max_int.c check_min_max.c

OBJS = ${SRCS:.c=.o}

NAME = philo

CC = gcc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror -g3

PTHLIB = -lpthread

SANITIZE	?= 0

ifeq ($(SANITIZE), 1)
CFLAGS += -fsanitize=thread
else ifeq ($SANITIZE), 2)
CFLAGS += -fsanitize=address
endif
.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${PTHLIB}

all: ${NAME}

clean:
	${RM} ${OBJS}

fclean : clean
	${RM} ${NAME}

re: fclean all
