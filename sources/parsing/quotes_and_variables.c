/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_and_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:56:04 by eberkowi          #+#    #+#             */
/*   Updated: 2024/11/04 14:15:18 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	helper_for_redirects(t_main *main, t_tokens **tokens, int token_id)
{
	t_redirect_node	*temp;

	temp = (*tokens)[token_id].redirects;
	while (temp)
	{
		if (temp->type == INFILE || temp->type == OUTFILE || temp->type == APPEND)
		{	
			if (!expand_quotes_and_vars(main, tokens, &(temp->name), false))
				free_all_and_exit_with_free_split_middle(main, tokens);
		}
		if (check_for_outside_quotes(temp->delimiter, NULL))
		{
			temp->delimiter_has_quotes = true;
			if (!remove_outside_quotes(&temp->delimiter))
				free_all_and_exit_with_free_split_middle(main, tokens);
		}
		temp = temp->next;
	}	
}

void	quotes_and_variables(t_main *main, t_tokens **tokens)
{
	int	token_id;
	int	cmd_id;

	token_id = 0;
	cmd_id = 0;
	while (token_id < main->num_of_pipes + 1)
	{
		cmd_id = 0;
		if ((*tokens)[token_id].command)
		{
			while ((*tokens)[token_id].command[cmd_id])
			{
				if (!expand_quotes_and_vars(main, tokens
						, &(*tokens)[token_id].command[cmd_id], false))
					free_and_exit_quote_malloc(main, tokens, token_id, cmd_id);
				cmd_id++;
			}
		}
		helper_for_redirects(main, tokens, token_id);
		token_id++;
	}
}
