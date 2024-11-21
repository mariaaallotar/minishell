/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:12:47 by eberkowi          #+#    #+#             */
/*   Updated: 2024/11/20 16:29:14 by eberkowi         ###   ########.fr       */
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
		node = (*tokens)[i].redirects;
		while (node != NULL)
		{
			if (node->name)
			{
				if (node->type == HEREDOC && !access(node->name, F_OK))
					unlink(node->name);
			}
			node = node->next;
		}
		i++;
	}
}

static void	execute_and_free(t_main *main, t_tokens **tokens)
{
	execute_commandline(main, *tokens);
	remove_heredocs(main, tokens);
	free_and_null_split_input(main);
	free_token_commands(main, tokens);
	free_token_redirects(main, tokens);
	free(*tokens);
}

static void	free_env_and_clear_history(t_main *main)
{
	free_environment(&(main->env_list));
	rl_clear_history();
}

int	main(int argc, char *argv[], char *envp[])
{	
	t_main		main;
	t_tokens	*tokens;

	(void)argc;
	(void)*argv;
	initialize_variables(&main, &tokens);
	copy_env(envp, &main);
	while (1)
	{
		errno = 0;
		main.rl_return = handle_inputs(&main.input, &main);
		if (main.rl_return == -1)
			break ;
		else if (main.rl_return == 0)
			continue ;
		if (!parsing(&main, &tokens))
		{
			free_input_and_split(&main);
			continue ;
		}
		execute_and_free(&main, &tokens);
	}
	free_env_and_clear_history(&main);
	exit (main.exit_code);
}
