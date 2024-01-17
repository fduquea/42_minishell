# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fduque-a <fduque-a@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/17 10:57:36 by fduque-a          #+#    #+#              #
#    Updated: 2023/12/26 11:58:11 by arepsa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ------------ COLORS ------------ #
RESET	= \033[0m
BLACK 	= \033[1;30m
RED 	= \033[1;31m
GREEN 	= \033[1;32m
YELLOW 	= \033[1;33m
BLUE	= \033[1;34m
PURPLE 	= \033[1;35m
CYAN 	= \033[1;36m
WHITE 	= \033[1;37m

# ----------- COMMANDS ------------ #
CC = cc
RM = rm -rf

# ------------- FLAGS ------------- #
CFLAGS 	= -Wall -Werror -Wextra -g
LFLAGS 	= -L ./$(LIBFT_DIR) -lft -lreadline
MK_FLAG = --no-print-directory

# -------------- PATHS -------------- #
INC			= includes
SRC_DIR		= srcs
OBJ_DIR		= objs
LIBFT_DIR	= libft
SUB_DIR		= builtins clean_and_error environment executor expander heredoc lexer parser prompt signals
OBJS_DIRS	= $(foreach dir, $(SUB_DIR), $(addprefix $(OBJ_DIR)/, $(dir)))

# /------------- FILES ------------- #
NAME 		= minishell
LIBFT		= $(LIBFT_DIR)/libft.a
FILES 		= builtins/b_main builtins/b_pwd builtins/b_echo builtins/b_env \
		builtins/b_cd builtins/b_exit builtins/b_unset builtins/b_export builtins/b_export_utils \
		clean_and_error/clean clean_and_error/clean_lexer clean_and_error/clean_shell \
		clean_and_error/error clean_and_error/error_msg \
		environment/env_utils environment/env environment/envlst_use \
		executor/executor executor/cmd_handling executor/executor_utils \
		executor/cmd_utils executor/path \
		expander/expander expander/expand_arg expander/expand_utils \
		heredoc/heredoc_utils heredoc/heredoc heredoc/open_pipe heredoc/pipe_utils \
		lexer/lexer_utils lexer/lexer \
		parser/parser_utils parser/parser \
		prompt/prompt \
		signals/signals signals/signals_aux \
		main
SRC 		= $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(FILES)))
OBJ 		= $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(FILES)))

# -------------- RULES --------------- #
all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LFLAGS) -o $(NAME) -I $(INC)
	@echo "[$(GREEN)$(NAME) created$(RESET)]"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) $(OBJS_DIRS)
	@echo "[$(GREEN)objs directory created$(RESET)]"

$(LIBFT):
	@make $(MK_FLAG) -C ./$(LIBFT_DIR)

clean:
	@$(RM) $(OBJ_DIR) $(OBJS_DIRS)
	@make $(MK_FLAG) -C ./$(LIBFT_DIR) clean
	@echo "[$(RED)objs removed$(RESET)]"
	@$(RM) output.log
	@$(RM) readline.supp

fclean: clean
	@$(RM) $(NAME) $(LIBFT)
	@echo "[$(RED)executables and $(LIBFT) removed$(RESET)]"

re: fclean all

# valgrind --leak-check=full -s --show-leak-kinds=all --track-origins=yes

leaks: readline.supp
	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes --log-file=output.log ./minishell

readline.supp:
	echo "{" > readline.supp
	echo "    leak readline" >> readline.supp
	echo "    Memcheck:Leak" >> readline.supp
	echo "    ..." >> readline.supp
	echo "    fun:readline" >> readline.supp
	echo "}" >> readline.supp
	echo "{" >> readline.supp
	echo "    leak add_history" >> readline.supp
	echo "    Memcheck:Leak" >> readline.supp
	echo "    ..." >> readline.supp
	echo "    fun:add_history" >> readline.supp
	echo "}" >> readline.supp

.PHONY: all clean fclean re test
