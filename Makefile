# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eholzer <eholzer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/21 09:34:30 by eholzer           #+#    #+#              #
#    Updated: 2023/03/13 11:01:45 by eholzer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

SRCS_LIST	=	main.c \
				ft_atoi.c \
				init.c \
				routine.c \
				utils.c \
				thread.c
SRCS_DIR	=	sources/
SRCS		=	${addprefix ${SRCS_DIR}, ${SRCS_LIST}}

OBJS_LIST	=	${SRCS_LIST:.c=.o}
OBJS_DIR	=	objects/
OBJS		=	${addprefix ${OBJS_DIR}, ${OBJS_LIST}}

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -pthread

all:			${NAME}

${OBJS_DIR}:
				mkdir ${OBJS_DIR}

${OBJS_DIR}%.o: ${SRCS_DIR}%.c
				${CC} ${CFLAGS} -c $^ -o $@

${NAME}:		${OBJS_DIR} ${OBJS}
				${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
				rm -rf ${OBJS_DIR}

fclean:			clean
				rm -f ${NAME}

re:				fclean all

.PHONY:			all clean fclean re