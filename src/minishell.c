/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:34:16 by malaakso          #+#    #+#             */
/*   Updated: 2023/06/14 12:34:38 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_prompt(void)
{
	char	*input;

	// mitigate_signals();
	while (1)
	{
		input = get_input();
		if (input)
		{
		// 	lexer(input);
			ft_printf(">>>>%s<<<<\n", input);
			free(input);
		}
	}
}

int	main(void)
{
	display_prompt();
	return (0);
}
