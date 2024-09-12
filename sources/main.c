/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:12:47 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/12 12:25:29 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

display_prompt_and_wait_for_input()
{
	char *line;
	
	line = readline("prompt: "); //TODO Change to set directly in struct
}

void handle_input(char *input)
{
	display_prompt_and_wait_for_input();
	add_input_to_history(input);
}

int	main(int argc, char *argv[])
{
	(void) argc;
	(void) argv;
	char *env_copy; //What data structure is this?
	int	status;

	copy_env(); 
	create_signals();
	while (1)
	{
		handle_input();
		if (exit_requested())
			free_and_exit();
		parse_and_tokenize_and_tree_the_tokens();
		apply_commands_in_tree(status);
		set_exit_status_of_last_line(main_struct.status);
	}
	free(env_copy);
	free_signals();
	
	return (0);
}
