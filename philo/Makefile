# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jterrada <jterrada@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/14 21:11:29 by jordi             #+#    #+#              #
#    Updated: 2025/03/07 12:33:29 by jterrada         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = philo
SRC = philo.c utils.c parsing.c safe_functions.c checks.c init.c start.c \
		sync.c clean.c setters.c write.c
OBJ = $(SRC:.c=.o)
HEADERS = -I. -pthread

all: $(NAME)

$(NAME): $(OBJ) Makefile philo.h
	@echo "🚧 Building $(NAME) executable..."
	@$(CC) $(OBJ) $(HEADERS) -o $(NAME)
	@echo "🎉 $(NAME) ready to play!\n"

%.o: %.c philo.h
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "🧹 Cleaned up object files!\n"

fclean: clean
	@rm -f $(NAME)
	@echo "🧹 Executable cleaned!\n"

re: fclean all

.PHONY: all clean fclean re