/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_and_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:56:04 by eberkowi          #+#    #+#             */
/*   Updated: 2024/10/22 10:56:34 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//"xxx$ONE'yyy$TWO'zzz"
//"xxx$HOME'yyy$USER'zzz"
//cat "command'$USER" < "infile'$USER" > "outfile'$USER'outfile" >> "append$USER"

//Left off here! Now works for commands, infiles and outfiles. 
//Also just added functionality that 'deleted' the $VAR if it wasn't found in the environment
//Works for doubles, singles, and no quotes
//Need to now expand heredocs?
//And lots of cleaning up long functions and lines and files

void quotes_and_variables(t_main *main, t_tokens **tokens)
{
	int token_id;
	int cmd_id;
	t_redirect_node *temp;

	token_id = 0;
	cmd_id = 0;
	while (token_id < main->num_of_pipes + 1)
	{
		cmd_id = 0;
		if ((*tokens)[token_id].command)
		{
			while ((*tokens)[token_id].command[cmd_id])
			{
				if (!expand_quotes_and_vars(main, tokens, &(*tokens)[token_id].command[cmd_id]))
					free_and_exit_quote_malloc_failed(main, tokens, token_id, cmd_id);
				cmd_id++;
			}
		}
		temp = (*tokens)[token_id].infiles;
		while (temp)
		{
			if (temp->type == INFILE)
			{	
				if (!expand_quotes_and_vars(main, tokens, &(temp->name)))
					free_all_and_exit_with_free_split_middle(main, tokens);
			}
			temp = temp->next;
		}
		temp = (*tokens)[token_id].outfiles;
		while (temp)
		{
			if (!expand_quotes_and_vars(main, tokens, &(temp->name)))
				free_all_and_exit_with_free_split_middle(main, tokens);
			temp = temp->next;
		}
		token_id++;
	}	
}
