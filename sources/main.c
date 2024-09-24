/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:12:47 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/24 17:50:28 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	initialize_variables(t_main *main, t_command **commands)
{
	main->input = NULL;
	main->split_input = NULL;
	main->exit_code = 0;
	*commands = NULL;
	main->env_list = NULL;
	main->num_of_pipes = 0;
}

int	main(int argc, char *argv[], char *envp[]) //what happens if ./minishell gets arguments?
{	
	t_main 	main;
	t_command *commands;

	(void)argc;
	(void)*argv;
	initialize_variables(&main, &commands);
	copy_env(envp, &main);
	// update_env(&main);	//do we do this at all?
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
	free_environment(&(main.env_list));
	//free_signals();
	exit (main.exit_code);
}
