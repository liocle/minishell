/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_validate_syntax.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lionel <lionel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:11:59 by lclerc            #+#    #+#             */
/*   Updated: 2023/06/26 18:12:13 by lionel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Syntax check as I have gathered it.. hopefully, nothing is missing:
1/ Check first character -> cannot be pipe
2/ Redirectors < < , <>,
	> > and pipes | | (beware of non combinable delimiters else than << and >>) have to be followed with at least one non-delimiter chars on each side (yeah,
		spaces can be in between)
3/ check quotes are closing 
4/ Last char cannot be redirector or pipe
Any syntax error exits back to prompt with "return FAILED_VALIDATION = 258"
*/

static void token_is_not_pipe(t_lexer *token_list, t_token *token)
{
	if (token != NULL && token->type == PIPE)
	{
		ft_printf("shellfish> syntax error near unexpected token `|'\n");
		token_list->state = SYNTAX_ERROR;
	}
}

static void	redirectors_are_valid(t_lexer *token_list, t_token *token)
{
	if (token->type == OUTFILE || token->type == INFILE
		|| token->type == HEREDOC || token->type == APPEND_TO)
	{
		token_list->state = token->type;
		if (token->next != NULL)
		{
			token = token->next;
			if (token->type == SPACE)
				delete_space_token(&token_list, token->token_count);
			if (token->type == STRING)
				token_list->state = STRING;
			else
			{
				ft_printf("shellfish> syntax error near unexpected token%c\n",
					token->type);
				token_list->state = SYNTAX_ERROR;
			}
		}
		else
		{
			ft_printf("shellfish> syntax error near unexpected token\
				`newline'\n");
		}
	}
}


/**
 * @brief 
 * 
 * @param token_list 
 * @return int 
 */
int	validate_syntax(t_lexer *token_list)
{
	t_token	*token;

	token = token_list->token_list;
	token_list->state = STRING;
	token_is_not_pipe(token_list, token);
	while (token->next != NULL)
	{
		redirectors_are_valid(token_list, token);
		pipes_are_valid(token_list);
		quotes_are_valid(token_list);
	}
	if (token_is_not_pipe(token_list, token));
	if (token_list->state == FAILED_VALIDATION)
		return (FAILED_VALIDATION);
	return (SUCCESS);
}
