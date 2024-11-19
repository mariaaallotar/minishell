/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:12:47 by eberkowi          #+#    #+#             */
/*   Updated: 2024/11/18 13:35:18 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	initialize_variables(t_main *main, t_tokens **tokens)
{
	main->input = NULL;
	main->split_input = NULL;
	main->exit_code = 0;
	*tokens = NULL;
	main->tokens = tokens;
	main->env_list = NULL;
	main->num_of_pipes = 0;
	main->elements_in_command = 0;
	main->id_command = 0;
	main->quote_split_length = 0;
	main->id_quote_split = 0;
}

void	remove_heredocs(t_main *main, t_tokens **tokens)
{
	t_redirect_node	*node;
	int				i;

	i = 0;
	while (i <= main->num_of_pipes)
	{
		node = (* tokens)[i].redirects;
		while (node != NULL)
		{
			if (node->type == HEREDOC)
				unlink(node->name);
			node = node->next;
		}
		i++;
	}
}

int	main(int argc, char *argv[], char *envp[])
{	
	t_main 	main;
	t_tokens *tokens;
	int		rl_return;

	(void)argc;
	(void)*argv;
	initialize_variables(&main, &tokens);
	tokens = NULL;
	copy_env(envp, &main);
	while (1)
	{
		errno = 0;
		rl_return = handle_inputs(&main.input, &main);
		if (rl_return == -1)
			break;
		else if (rl_return == 0)
			continue;
		if (!parsing(&main, &tokens))
		{
			if (main.input)
				free(main.input);
			ft_free_split(&main.split_input);
			continue;
		}
		execute_commandline(&main, tokens);
		remove_heredocs(&main, &tokens);
		free_and_null_split_input(&main);
		free_token_commands(&main, &tokens);
		free_token_redirects(&main, &tokens);
		free(tokens);
	}
	free_environment(&(main.env_list));
	rl_clear_history();
	exit (main.exit_code);
}
