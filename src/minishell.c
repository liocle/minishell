/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lionel <lionel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:34:16 by malaakso          #+#    #+#             */
/*   Updated: 2024/10/31 11:51:51 by lionel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_minishell    *g_minishell;

void	display_prompt(void)
{
	char	*input;

	while (1)
	{
		input = get_input();
		if (!input)
			return ;
		g_minishell->is_pipeline = 0;
		lexer(input);
	}
}

int	main(void)
{
	size_t	i;
	g_minishell = ft_calloc(1, sizeof(t_minishell));
	if (!g_minishell)
    	exit(1);

	g_minishell = ft_calloc(1, sizeof(t_minishell));
	if (!g_minishell)
		exit(1);
	if (init_envp())
		return (1);
	display_prompt();
	i = 0;
	while (g_minishell->envp[i])
		free(g_minishell->envp[i++]);
	vec_free(&g_minishell->env_vec);
	return (0);
}
