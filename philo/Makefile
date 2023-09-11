# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akuzmenk <akuzmenk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/22 12:48:28 by akuzmenk          #+#    #+#              #
#    Updated: 2023/07/27 15:49:07 by akuzmenk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo
INC = ./include
FLAGS := -Wall -Wextra -Werror -g #-fsanitize=thread

SRCS :=	\
	main.c \
	libft_atoi.c \
	init.c \
	philo_life.c \
	utils.c \
	kill_philos.c \
	

OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	cc $(FLAGS) $(OBJS) -o $(NAME) -pthread 

%.o: %.c
	cc $(FLAGS) -I $(INC) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	
re: fclean all

.PHONY: clean fclean re
