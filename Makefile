# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fduque-a <fduque-a@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/17 10:57:36 by damachad          #+#    #+#              #
#    Updated: 2023/09/20 13:00:57 by fduque-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ COLORS /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ #
RESET	= \033[0m
BLACK 	= \033[1;30m
RED 	= \033[1;31m
GREEN 	= \033[1;32m
YELLOW 	= \033[1;33m
BLUE	= \033[1;34m
PURPLE 	= \033[1;35m
CYAN 	= \033[1;36m
WHITE 	= \033[1;37m

# /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ COMMANDS /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ #
CC = cc
RM = rm -rf

# /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_ FLAGS _/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ #
CFLAGS 	= -Wall -Werror -Wextra -g
MK_FLAG = --no-print-directory
LFLAGS 	= -L ./libft -lft -lreadline

# /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_ PATHS _/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ #
INC			= include
SRC_DIR		= srcs
OBJ_DIR		= objs

# /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_ FILES _/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ #
NAME 		= minishell
LIBFT		= libft/libft.a
FILES 		= main lexer
SRC 		= $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(FILES)))
OBJ 		= $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(FILES)))

# /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_ ARGUMENTS _/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ #


# /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_ RULES _/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ #
all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LFLAGS) -o $(NAME) -I $(INC)
	echo "[$(GREEN)$(NAME) created$(RESET)]"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c 
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	echo "[$(GREEN)objs directory created$(RESET)]"

$(LIBFT):
	make $(MK_FLAG) -C ./libft

clean:
	$(RM) $(OBJ_DIR) $(OBJ_BNS_DIR)
	make $(MK_FLAG) -C ./libft clean
	echo "[$(RED)objs removed$(RESET)]"

fclean: clean
	$(RM) $(NAME) $(NAME_BNS) $(LIBFT)
	echo "[$(RED)executables and $(LIBFT) removed$(RESET)]"

re: fclean all

# valgrind --leak-check=full -s --show-leak-kinds=all --track-origins=yes

test: $(NAME)
	@./$(NAME)

.SILENT:

.PHONY: all clean fclean re test