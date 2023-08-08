# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lclerc <lclerc@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/09 12:33:11 by malaakso          #+#    #+#              #
#    Updated: 2023/07/30 11:44:49 by malaakso         ###   ########.fr        #
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

SHELL_H			=	minishell.h \
					env.h
SHELL_C			=	minishell.c \
					env.c

INPUT_H			=	input.h
INPUT_C			=	input.c

LEXER_H			=	lexer.h	
LEXER_C			=	lexer.c \
					lexer_utils.c \
					lexer_label_token_type.c \
					lexer_validate_syntax.c \
					lexer_validate_quotes.c \
					lexer_string_concatenation.c \
					lexer_validate_pipes.c \
					lexer_validate_redirectors.c \
					lexer_expansion.c \
					DELETE_ME_AND_FCT_IN_HEADER.c
					

ASTREE_H		=	ast.h
ASTREE_C		=	ast.c \
					ast_data_ops_helpers.c \
					ast_data_ops_alloc.c \
					ast_data_ops_free.c \
					ast_parse_command.c \
					ast_parse_argv.c \
					ast_parse_redirections.c

EXECUTOR_H		=	executor.h
EXECUTOR_C		=	executor.c \
					ex_execute_pipeline.c \
					ex_execute_command.c \
					ex_execute_bi_cmd.c

H_FILES			=	$(SHELL_H) $(INPUT_H) $(LEXER_H) $(ASTREE_H) $(EXECUTOR_H)
C_FILES			=	$(SHELL_C) $(INPUT_C) $(LEXER_C) $(ASTREE_C) $(EXECUTOR_C)

H_PATHS			=	$(addprefix $(H_FOLDER)/, $(H_FILES))
C_PATHS			=	$(addprefix $(C_FOLDER)/, $(C_FILES))
OBJ_PATHS		=	$(addprefix $(OBJ_FOLDER)/, \
					$(patsubst %.c, %.o, $(C_FILES)))

C_FLAGS_OBJ		=	-Wall -Wextra -Werror
C_FLAGS_NAME		=	$(C_FLAGS_OBJ) \
					-lreadline \
					-L ~/.brew/opt/readline/lib \
					-I ~/.brew/opt/readline/include

.PHONY: all
all: $(NAME)

$(NAME): $(FOLDER_LIST) $(OBJ_PATHS) Makefile \
	$(LIBFT_FOLDER)/$(LIBFT)
	@pkill minishell || true
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
