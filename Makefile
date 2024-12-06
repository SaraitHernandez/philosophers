# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/25 22:57:41 by sarherna          #+#    #+#              #
#    Updated: 2024/12/06 11:47:39 by sarherna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread 
OBJ_DIR = obj/
SRC_DIR = src/
UTILS_DIR = utils/
INCLUDES = -I include/

SRC = $(SRC_DIR)main.c \
      $(SRC_DIR)philosopher_actions.c \
      $(SRC_DIR)philosopher_states.c \
      $(SRC_DIR)philosopher_threads.c \
      $(SRC_DIR)simulation_initialization.c \
      $(SRC_DIR)health_monitor.c \
      $(UTILS_DIR)status_printing.c \
	$(UTILS_DIR)utils.c \
      $(UTILS_DIR)helper.c \
	$(UTILS_DIR)argument_validation.c \
      $(UTILS_DIR)libft.c \
      $(UTILS_DIR)argument_parsing.c \

OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c include/philosopher.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
