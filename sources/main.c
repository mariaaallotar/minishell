/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:12:47 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/18 13:00:31 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	copy_env()
{
	//do we get env from main envp or
	//from getenv()
}

void	initialize_variables(t_main *main)
{
	main->input = NULL;
	main->split_input = NULL;
	main->exit_code = 0;
}

int	main(void) //what happens if ./minishell gets arguments?
{
	//char 	*env_copy; //What data structure is this?
	t_main 	main;

	initialize_variables(&main);
	//copy_env();
	//create_signals();
	while (1)
	{
		handle_input(&main.input);
		parsing(&main);
		//parse_and_tokenize_and_tree_the_tokens();
		//apply_commands_in_tree(main.status);
		//set_exit_status_of_last_line(main.status);
	}
	if (main.input)
		free(main.input);
	//free(env_copy);
	//free_signals();
	
	exit (main.exit_code);
}
