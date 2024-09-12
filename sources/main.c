/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:12:47 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/12 11:54:11 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

display_prompt_and_wait_for_input()
{
	char *line; 
	
	line = readline("prompt: "); //TODO Change to set directly in struct
}

int	main(int argc, char *argv[])
{
	(void) argc;
	(void) argv;
	char *env_copy;

	copy_env(); 
	create_signals();
	while (1)
	{
		display_prompt_and_wait_for_input();
		if (exit_requested())
			free_and_exit();
		parse_and_tokenize();
		if (command_not_found())
			print_command_not_found();
		else
			token_binary_tree();
	}
	free(env_copy);
	free_signals();
	
	return (0);
}
