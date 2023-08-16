/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_execute_pipeline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:01:22 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/10 11:01:44 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	execute_pipeline(t_ast_node *node)
{
	int	pipe_end[2];

	if (pipe(pipe_end) < 0)
		exit(1);
	if (wrap_fork() == 0)
	{
		if (dup2(pipe_end[WRITING_END], STDOUT_FILENO) < 0)
			exit (1);
		close(pipe_end[READING_END]);
		executor(node->left);
		exit(g_minishell->exit_status);
	}
	wait(&g_minishell->termination_status);
	g_minishell->exit_status = ret_exit_status(
			g_minishell->termination_status);
	if (wrap_fork() == 0)
	{
		if (dup2(pipe_end[READING_END], STDIN_FILENO) < 0)
			exit (1);
		close(pipe_end[WRITING_END]);
		executor(node->right);
		exit(g_minishell->exit_status);
	}
	wait(&g_minishell->termination_status);
	g_minishell->exit_status = ret_exit_status(
			g_minishell->termination_status);
	close(pipe_end[READING_END]);
	close(pipe_end[WRITING_END]);
}