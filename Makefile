# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fduque-a <fduque-a@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/14 10:28:01 by fduque-a          #+#    #+#              #
#    Updated: 2023/09/14 16:58:44 by fduque-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COLORS    ---------------------------------------------------->
    # \e[ : Start color scheme.
    # x;y : Color pair to use (x;y)
RESET	= \033[0m
BLACK 	= \033[1;30m
RED 	= \033[1;31m
GREEN 	= \033[1;32m
YELLOW 	= \033[1;33m
BLUE	= \033[1;34m
PURPLE 	= \033[1;35m
CYAN 	= \033[1;36m
WHITE 	= \033[1;37m

# COMMANDS ---------------------------------------------------->


# FLAGS    ---------------------------------------------------->
CFLAGS	= -Wall -Wextra -Werror -g -fsanitize=address

# FOLDERS  ---------------------------------------------------->
LIBFT_DIR	= libft_curr

# FILES    ---------------------------------------------------->
NAME	= minishell
FILES	= src
OBJECTS	= $(FILES:.c=.o)

# RULES    ---------------------------------------------------->

all: $(NAME)

$(NAME):
	make --no-print-directory -C $(LIBFT_DIR)

clean:

fclean: clean
	$(MAKE) fclean --no-print-directory -C $(LIBFT_DIR)

re: fclean all

bash:
	clear
	./minishell

redo: re bash

.SILENT:

.PHONY: all clean fclean re bash redo