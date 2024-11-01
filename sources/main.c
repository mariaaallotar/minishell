/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:12:47 by eberkowi          #+#    #+#             */
/*   Updated: 2024/11/01 14:23:06 by maheleni         ###   ########.fr       */
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
}

void	remove_heredocs(t_main *main, t_tokens **tokens)
{
	t_redirect_node	*node;
	int				i;

	i = 0;
	while (i <= main->num_of_pipes)
	{
		node = (* tokens)[i].infiles;
		while (node != NULL)
		{
			if (node->type == HEREDOC)
				unlink(node->name);
			node = node->next;
		}
		i++;
	}
}

int	main(int argc, char *argv[], char *envp[]) //what happens if ./minishell gets arguments?
{	
	t_main 	main;
	t_tokens *tokens;
	int		rl_return;

	(void)argc;
	(void)*argv;
	initialize_variables(&main, &tokens);
	copy_env(envp, &main);
	// update_env(&main);	//do we do this at all?
	while (1)
	{
		errno = 0;
		rl_return = handle_inputs(&main.input);
		if (rl_return == -1)
			break;
		else if (rl_return == 0)
			continue;
		if (!parsing(&main, &tokens))
		{
			remove_heredocs(&main, &tokens);
			free(main.input);
			ft_free_split(&main.split_input);
			continue;
		}
		execute_commandline(&main, tokens);
		//set_exit_status_of_last_line();
		remove_heredocs(&main, &tokens);
		free_and_null_split_input(&main);
		free_token_commands(&main, &tokens);
		free_token_redirects(&main, &tokens);
		free(tokens);
	}
	free_environment(&(main.env_list));
	rl_clear_history();
	//free_signals();
	exit (main.exit_code);		//just 0? I don't think we ever
}
