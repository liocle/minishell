/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_execute_pipeline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:01:22 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/24 09:48:53 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	sig_pipeline(int sig)
{
	ioctl(0, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	if (sig == SIGINT)
	{
		kill(g_minishell->pid_pipeline[0], SIGINT);
		kill(g_minishell->pid_pipeline[1], SIGINT);
	}
	else if (sig == SIGQUIT)
	{
		kill(g_minishell->pid_pipeline[0], SIGQUIT);
		kill(g_minishell->pid_pipeline[1], SIGQUIT);
		ft_putstr_fd("Quit: 3\n", 1);
	}
}

static void	execute_pipeline_fork_left(pid_t *ext_pid,
	t_ast_node *node, int *pipe_end)
{
	if (wrap_fork(&g_minishell->pid_pipeline[0]) == 0)
	{
		if (dup2(pipe_end[WRITING_END], STDOUT_FILENO) < 0)
			exit (1);
		close(pipe_end[READING_END]);
		executor(node->left);
		close(pipe_end[WRITING_END]);
		exit(g_minishell->exit_status);
	}
}

static void	execute_pipeline_fork_right(pid_t *ext_pid,
	t_ast_node *node, int *pipe_end)
{
	if (wrap_fork(&g_minishell->pid_pipeline[1]) == 0)
	{
		if (dup2(pipe_end[READING_END], STDIN_FILENO) < 0)
			exit (1);
		executor(node->right);
		close(pipe_end[READING_END]);
		exit(g_minishell->exit_status);
	}
}

void	execute_pipeline(t_ast_node *node)
{
	int		pipe_end[2];

	if (pipe(pipe_end) < 0)
		exit(1);
	execute_pipeline_fork_left(&g_minishell->pid_pipeline[0], node, pipe_end);
	close(pipe_end[WRITING_END]);
	execute_pipeline_fork_right(&g_minishell->pid_pipeline[1], node, pipe_end);
	close(pipe_end[READING_END]);
	signal(SIGINT, sig_pipeline);
	signal(SIGQUIT, sig_pipeline);
	waitpid(g_minishell->pid_pipeline[0], &g_minishell->termination_status, 0);
	waitpid(g_minishell->pid_pipeline[1], &g_minishell->termination_status, 0);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	g_minishell->exit_status = ret_exit_status(
			g_minishell->termination_status);
}
