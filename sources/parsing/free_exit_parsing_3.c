/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit_parsing_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:44:31 by eberkowi          #+#    #+#             */
/*   Updated: 2024/11/08 10:24:18 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_and_exit_quote_malloc(t_main *main, t_tokens **tokens
		, int token_id, int cmd_id)
{
	int	i;

	i = 1;
	while ((*tokens)[token_id].command[cmd_id + i])
	{
		free((*tokens)[token_id].command[cmd_id + i]);
		i++;
	}
	free_and_null_split_input(main);
	free_token_commands(main, tokens);
	free_token_redirects(main, tokens);
	free(*tokens);
	free_environment(&(main->env_list));
	exit (1);
}

void	free_and_exit_combine_elements(t_main *main, t_tokens **tokens
		, char ***quote_split)
{
	print_error("Error: Failed to malloc temp var for quote_split combine\n");
	ft_free_split(quote_split);
	free_all_and_exit(main, tokens);
}

void	free_and_exit_quote_split_expand(t_main *main, t_tokens **tokens
		, char ***quote_split, int i)
{
	i++;
	while ((*quote_split)[i])
	{
		free((*quote_split)[i]);
		i++;
	}
	ft_free_split(quote_split);
	free_all_and_exit(main, tokens);
}

int pipe_syntax_error(t_main *main, t_tokens **tokens)
{
	print_error("Error: syntax error near unexpected token `|'\n");
	main->exit_code = 2;
	free(*tokens);
	return (1);
}
