/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:12:47 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/20 15:40:10 by maheleni         ###   ########.fr       */
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
}

int	main(int argc, char *argv[], char *envp[]) //what happens if ./minishell gets arguments?
{
	t_main 	main;
	t_command *commands;

	(void)argc;
	(void)*argv;
	initialize_variables(&main, &commands);
	copy_env(envp, &main);


	// // update_env(&main);	//do we do this at all?
	// //create_signals();
	// while (1)
	// {
	// 	// handle_inputs(&main.input);
	// 	// parsing(&main, &commands);
	// 	//apply_commands_in_tree();
	// 	//set_exit_status_of_last_line();
	// 	break;
	// }
	// if (main.input)
	// 	free(main.input);

	print_linked_list(main.env_list);

	chdir("..");							//works without PWD
	char *my_argv[] = {"ls", NULL};
	// char *buf = malloc (100);
	// printf("\n%s\n", getcwd(buf, 100));		//works even without PWD
	pwd();
	execve("/bin/ls", my_argv, envp);

	free_environment(&(main.env_list));
	//free_signals();
	exit (main.exit_code);
}
