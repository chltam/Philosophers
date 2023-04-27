# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: htam <htam@student.42berlin.de>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/16 18:49:19 by htam              #+#    #+#              #
#    Updated: 2023/04/26 17:26:19 by htam             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= philo

CC		:= cc
CFLAGS	:= -Werror -Wextra -Wall

SCRS	:= main.c valid_error.c init.c action.c action_helper.c


$(NAME): $(SCRS)
	$(CC) $(SCRS) -pthread $(CFLAGS) -o $(NAME)

all:	$(NAME)


clean:
	rm -rf $(NAME)

fclean:
	rm -rf $(NAME)

re:	fclean all