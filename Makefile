# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/09 12:33:11 by malaakso          #+#    #+#              #
#    Updated: 2023/06/09 20:42:18 by malaakso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell
LIBFT			=	libft.a
COMPILER		=	cc

H_FOLDER		=	inc
C_FOLDER		=	src
OBJ_FOLDER		=	obj
LIBFT_FOLDER		=	libft
FOLDER_LIST		=	$(H_FOLDER) $(C_FOLDER) $(OBJ_FOLDER) \
					$(LIBFT_FOLDER)

MAIN_H			=	minishell.h
MAIN_C			=	minishell.c

INPUT_H			=	
INPUT_C			=	input.c

LEXER_H			=	
LEXER_C			=	

H_FILES			=	$(MAIN_H) $(INPUT_H) $(LEXER_H)
C_FILES			=	$(MAIN_C) $(INPUT_C) $(INPUT_H)

H_PATHS			=	$(addprefix $(H_FOLDER)/, $(H_FILES))
C_PATHS			=	$(addprefix $(C_FOLDER)/, $(C_FILES))
OBJ_PATHS		=	$(addprefix $(OBJ_FOLDER)/, \
					$(patsubst %.c, %.o, $(C_FILES)))

C_FLAGS_OBJ		=	-Wall -Wextra -Werror -lreadline
C_FLAGS_NAME		=	$(C_FLAGS_OBJ)

.PHONY: all
all: $(NAME)

$(NAME): $(FOLDER_LIST) $(OBJ_PATHS) Makefile \
	$(LIBFT_FOLDER)/$(LIBFT)
	$(COMPILER) $(C_FLAGS_NAME) $(OBJ_PATHS) $(LIBFT_FOLDER)/$(LIBFT) -o $@

$(OBJ_PATHS): $(OBJ_FOLDER)/%.o:$(C_FOLDER)/%.c $(H_PATHS) Makefile
	$(COMPILER) $(C_FLAGS_OBJ) -I $(H_FOLDER) -I $(LIBFT_FOLDER) -c $< -o $@

$(LIBFT_FOLDER)/$(LIBFT):
	$(MAKE) -C $(LIBFT_FOLDER)

$(FOLDER_LIST):
	mkdir $@

.PHONY: clean
clean:
	rm -f $(OBJ_PATHS)
	rm -rf $(OBJ_FOLDER)
	$(MAKE) fclean -C $(LIBFT_FOLDER)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all