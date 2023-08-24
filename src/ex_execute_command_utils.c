/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_execute_command_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 11:37:00 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/24 11:44:14 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_signal(int termination_status)
{
	int	sig_num;

	if (WIFEXITED(termination_status) || !WIFSIGNALED(termination_status))
		return ;
	sig_num = WTERMSIG(termination_status);
	if (sig_num == SIGINT)
		ft_putchar_fd('\n', 1);//check this against real behavior
	else if (sig_num == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", 2);//check this against real behavior
}

t_bool	is_absolute_path(t_ast_node *node)
{
	int		i;

	i = 0;
	while (node->exec_argv[0][i])
	{
		if (node->exec_argv[0][i] == '/')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

static char	**parse_path_ret_split(char *path)
{
	char	**split_path;
	char	*tmp;

	tmp = ft_strdup(path);
	split_path = ft_split(tmp, ':');
	free(tmp);
	if (!split_path)
		exit(1);
	return (split_path);
}

static int	parse_path_check_access(t_ast_node *node, char *found_file)
{
	int	ret;

	ret = access(found_file, X_OK);
	if (ret == 0)
	{
		free(node->exec_file);
		node->exec_file = found_file;
	}
	return (ret);
}

void	parse_path(t_ast_node *node)
{
	char	**split_path;
	int		i;
	char	*found_file;

	found_file = (char *)env_get_value_by_key("PATH");
	if (!found_file)
		return ;
	split_path = parse_path_ret_split(found_file);
	i = 0;
	while (split_path[i] != NULL)
	{
		found_file = env_utils_join_three_str(
				split_path[i], "/", node->exec_argv[0]);
		if (parse_path_check_access(node, found_file) == 0)
			break ;
		free(found_file);
		i++;
	}
	i = 0;
	while (split_path[i] != NULL)
		free(split_path[i++]);
	free(split_path);
}
