# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/17 13:01:23 by mmoreira          #+#    #+#              #
#    Updated: 2022/02/20 14:42:10 by mmoreira         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#--------------------------------------//---------------------------------------
SRC_DIR	=	./sources/system \
			./sources/read_and_adjust \
			./sources/split_and_tokenizer \
			./sources/exec_all_commands \
			./sources/builtins \

SRC		=	minishell.c \
			var_operations.c \
			signal.c \
			free_functions.c \
			\
			adjust_redirects.c \
			adjust_dollar.c \
			\
			split_line.c \
			check_command.c \
			tokenizer.c \
			\
			set_fd_and_args.c \
			here_document.c \
			functions_exec.c \
			exec_builtins.c \
			exec_no_builtins.c \
			\
			cd.c \
			echo.c \
			env.c \
			exit.c \
			export.c \
			pwd.c \
			unset.c \

OBJ_DIR	=	./builds
OBJ		=	$(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

INCD_DIR=	./includes
INCD	=	minishell.h
#--------------------------------------//---------------------------------------
vpath %.c $(SRC_DIR)
vpath %.h $(INCD_DIR)

NAME	=	minishell

MODULE	=	./Libft/libft.a

CFLAGS	=	-Wall -Wextra -Werror -g3 -fsanitize=address

FLAGS	=	-lreadline -lncurses

RM		=	rm -rf

CC		=	clang
#--------------------------------------//---------------------------------------
all:			$(NAME)

$(NAME):	$(MODULE) $(OBJ)
	$(CC) $(CFLAGS) $(FLAGS) $(OBJ) $(MODULE) -I $(INCD_DIR) -o $(NAME)
	@echo "\033[1;32m"
	@echo "/ ************************************ \\"
	@echo "|           minishell Criado           |"
	@echo "\\ ************************************ /"
	@echo "\033[0m"

$(MODULE):
	make -C Libft

$(OBJ_DIR)/%.o:	%.c $(INCD)
	mkdir -p $(OBJ_DIR)
	$(CC) -c -o $@ $(CFLAGS) -I $(INCD_DIR) $<
#--------------------------------------//---------------------------------------
clean:
	$(RM) $(OBJ_DIR)
	make clean -C Libft
	@echo "\033[1;31m"
	@echo "/ ************************************ \\"
	@echo "|        Arquivos .o Deletados         |"
	@echo "\\ ************************************ /"
	@echo "\033[0m"

fclean:		clean
	$(RM) $(NAME)
	make aclean -C Libft
	@echo "\033[1;31m"
	@echo "/ ************************************ \\"
	@echo "|          minishell Deletado          |"
	@echo "\\ ************************************ /"
	@echo "\033[0m"
#--------------------------------------//---------------------------------------
install:
	@sudo apt-get -y install libreadline-dev
\
re:			fclean all

git:
	@git add .
	@git status
	@git commit -m "$m"

.PHONY:		all clean fclean re git
