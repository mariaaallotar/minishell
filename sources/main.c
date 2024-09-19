/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:12:47 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/19 14:52:06 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	initialize_variables(t_main *main)
{
	main->input = NULL;
	main->split_input = NULL;
	main->exit_code = 0;
	main->env_list = NULL;
}

int	main(int argc, char *argv[], char *envp[]) //what happens if ./minishell gets arguments?
{
	t_main 	main;

	initialize_variables(&main);
	copy_env(envp, &main);
	//update_env(&main);	//do we do this at all?

	print_linked_list(main.env_list);
	add_variable(&main, "MYVAR=hahah");
	printf("\n\n");
	print_linked_list(main.env_list);

	// //create_signals();
	// while (1)
	// {
	// 	handle_inputs(&main.input);
	// 	parsing(&main);
	// 	//apply_commands_in_tree();
	// 	//set_exit_status_of_last_line();
	// }
	// if (main.input)
	// 	free(main.input);
	free_environment(&(main.env_list));
	//free_signals();
	exit (main.exit_code);
}
