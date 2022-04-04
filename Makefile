# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/04 16:29:52 by aherrero          #+#    #+#              #
#    Updated: 2022/04/04 17:43:38 by aherrero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = minishell.c \

OBJ = $(SRC:.c=.o)

GREEN = \033[1;32m
RED = \033[1;31m
YEL = \033[1;33m
WHT = \033[1;37m
EOC = \033[1;0m

HEADERS = includes/minishell.h
LIBFT = libft/libft.a
CC = gcc

READLINE_DIR = ~/.brew/Cellar/readline/8.1.2


FLAGS = -Wall -Wextra -Werror -I $(READLINE_DIR)/include/ -L $(READLINE_DIR)/lib/ -lreadline -g3 -fsanitize=address

.c.o: $(SRC)
	@$(CC) $(FLAGS) -c -o $@ $<


$(NAME):$(OBJ)
		@echo "$(WHT)Compiling libraries...$(EOC)"
		@${MAKE} -C libft
		@echo "$(GREEN)Libraries done.$(EOC)"
		@echo "$(WHT)Compiling Minishell...$(EOC)"
		@$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT)
		@echo "$(GREEN)Minishell build completed.$(EOC)"

all: $(NAME)

clean:
		@echo "$(WHT)Removing o-files...$(EOC)"
		@/bin/rm -f $(OBJ)
		@${MAKE} -C libft clean
		@echo "$(GREEN)Clean done.$(EOC)"

fclean: clean
		@echo "$(WHT)Removing object- and binary -files...$(EOC)"
		@/bin/rm -f $(NAME)
		@${MAKE} -C libft fclean
		@echo "$(GREEN)fclean done.$(EOC)"

re: fclean all

.PHONY: all clean fclean re bonus