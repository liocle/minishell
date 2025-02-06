/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lionel <lionel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:34:09 by malaakso          #+#    #+#             */
/*   Updated: 2024/10/31 11:47:24 by lionel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Provides constants for system limits, such as maximum path length.
# include <limits.h>

// Provides types
# include <sys/types.h>

// Contains general-purpose functions like malloc, free, exit, getenv.
# include <stdlib.h>

// Includes write, access, read, close, fork, getcwd, chdir, stat, lstat,
// fstat, unlink, execve, dup, dup2, pipe, isatty, ttyname, tcsetattr,
// tcgetattr, and others.
# include <unistd.h>

// Necessary includes for readline.
# include <readline/history.h>
# include <readline/readline.h>

// Includes signal, sigaction, sigemptyset, sigaddset, kill.
# include <signal.h>

// Includes open.
# include <fcntl.h>

// Includes sterror.
# include <string.h>

// Defines the errno global variable and various error codes.
# include <errno.h>

// Includes tcsetattr and tcgetattr specific to the current terminal.
# include <termios.h>

// For ioctl
# include <sys/ioctl.h>

// For stat
# include <sys/stat.h>

// For waitpid on Linux
# include <sys/wait.h>

// User defined headers
# include "../libft/libft.h"
# include "ast.h"
# include "env.h"
# include "executor.h"
# include "input.h"
# include "lexer.h"

typedef struct s_minishell
{
	int				exit_status;
	int				termination_status;
	t_vec			env_vec;
	char			**envp;
	int				is_pipeline;
	int				pid_pipeline[2];
	int				pid_single;
}					t_minishell;

typedef enum e_bool
{
	FALSE,
	TRUE
}				t_bool;

extern t_minishell			*g_minishell;

// Necessary function prototype for readline.
void				rl_replace_line(const char *text, int clear_undo);

// Function prototypes for user created functions
void				display_prompt(void);
t_return_value		lexer(char *input);
t_ast_node			*ast_builder(t_token *token);
void				executor(t_ast_node *node);

// Builtins
void				ft_pwd(void);
void				ft_echo(t_ast_node *node);
void				ft_cd(t_ast_node *node);
void				ft_exit(t_ast_node *node);
void				ft_unset(t_ast_node *node);
void				ft_export(t_ast_node *node);

#endif
