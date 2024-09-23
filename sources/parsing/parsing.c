/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:32:36 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/20 13:28:06 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int get_number_of_pipes(t_main *main)
{
	int i;
	int result;

	i = 0;
	result = 0;
	while (main->split_input[i])
		if (main->split_input[i++][0] == '|')
			result++;
	return (result);	
}

static void	malloc_commands(t_main *main, t_command **commands, int size)
{
	*commands = malloc((size) * sizeof(t_command));
	if (!*commands)
	{
		ft_free_split(&main->split_input);
		printf("Error: Failed to malloc\n");
		exit (1);
	}	
}

static void	initialize_commands(t_command **commands, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		(*commands)[i].null_terminate = false;
		(*commands)[i].command = NULL;
		(*commands)[i].flags = NULL;
		(*commands)[i].heredoc_delimiter = NULL;
		(*commands)[i].redirect_in = NULL;
		(*commands)[i].redirect_out = NULL;
		(*commands)[i].redirect_heredoc = false;
		(*commands)[i].redirect_append = NULL;
		i++;
	}
	(*commands)[size -1].null_terminate = true;
}

static void malloc_and_init_commands(t_main *main, t_command **commands)
{
	int num_of_pipes;

	num_of_pipes = get_number_of_pipes(main);
	malloc_commands(main, commands, num_of_pipes + 2);
	initialize_commands(commands, num_of_pipes + 2);
}

//Left off here fighting with malloc for command arrays

int	parsing(t_main *main, t_command **commands)
{
	//main functions
	if (!split_input(main))
		return (0);

	//print for testing
	int i = 0;
	while (main->split_input[i])
	{
		printf("input[%d] = %s\n", i, main->split_input[i]);
		i++;
	}
	
	//free input
	if (*main->input)
	{
		free(main->input);
		main->input = NULL;
	}
	
	//exit command builtin
	exit_command(main);

	// ------------------------------------------------------------------------
	
	//malloc commands array based on number of pipes
	malloc_and_init_commands(main, commands);

	// (*commands)[0].command = &(main->split_input[0]);
	// (*commands)[1].command = &(main->split_input[1]);
	// printf("command in parsing = %s\n", *((*commands)[0].command));
	// printf("command in parsing = %s\n", *((*commands)[1].command));
	free(*commands);

	// ------------------------------------------------------------------------
	
	//free and null
	if (main->split_input) //REMOVE
	{
		ft_free_split(&main->split_input);
		main->split_input = NULL;
	}
	return (1);
}
