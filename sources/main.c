/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:12:47 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/20 10:32:41 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	initialize_variables(t_main *main, t_commands **commands)
{
	main->input = NULL;
	main->split_input = NULL;
	main->exit_code = 0;
	*commands = NULL;
}

int	main(void) //what happens if ./minishell gets arguments?
{
	char 	*env_copy; //What data structure is this?
	t_main 	main;
	t_commands *commands;

	initialize_variables(&main, &commands);
	//copy_env();
	//create_signals();
	while (1)
	{
		handle_inputs(&main.input);
		parsing(&main, &commands);
		//apply_commands_in_tree();
		//set_exit_status_of_last_line();
	}
	if (main.input)
		free(main.input);
	free(env_copy);
	//free_signals();
	exit (main.exit_code);
}
