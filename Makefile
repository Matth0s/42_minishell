# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/17 13:01:23 by mmoreira          #+#    #+#              #
#    Updated: 2021/09/23 00:29:22 by mmoreira         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#--------------------------------------//---------------------------------------
SRC_DIR	=	./sources
SRC		=	minishell.c var_operations.c correct_line.c

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
	@echo ""
	@echo "/ ************************************ \\"
	@echo "|           minishell Criado           |"
	@echo "\\ ************************************ /"
	@echo ""

$(MODULE):
	make -C Libft

$(OBJ_DIR)/%.o:	%.c $(INCD)
	mkdir -p $(OBJ_DIR)
	$(CC) -c -o $@ $(CFLAGS) -I $(INCD_DIR) $<
#--------------------------------------//---------------------------------------
clean:
	$(RM) $(OBJ_DIR)
	make clean -C Libft
	@echo ""
	@echo "/ ************************************ \\"
	@echo "|        Arquivos .o Deletados         |"
	@echo "\\ ************************************ /"
	@echo ""

fclean:		clean
	$(RM) $(NAME)
	make aclean -C Libft
	@echo ""
	@echo "/ ************************************ \\"
	@echo "|          minishell Deletado          |"
	@echo "\\ ************************************ /"
	@echo ""
#--------------------------------------//---------------------------------------
install:
	@sudo apt-get -y install libreadline6-dev
\
re:			fclean all

git:
	@git add .
	@git status
	@git commit -m "$m"

.PHONY:		all clean fclean re git
