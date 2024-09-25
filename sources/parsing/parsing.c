/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:32:36 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/25 13:34:15 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void print_split_input(t_main *main) //REMOVE
{
	printf("\033[0;33m---SPLIT_INPUT---\033[0m\n");
	int i = 0;
	while (main->split_input[i])
	{
		printf("input[%d] = %s\n", i, main->split_input[i]);
		i++;
	}
	printf("\n");
}

static void print_command_structs(t_main *main, t_command **command) //REMOVE
{
	int command_number = 0;
	int i = 0;
	while (command_number < main->num_of_pipes + 1)
	{
		printf("\033[0;32m---COMMAND %d---\033[0m\n", command_number);
		i = 0;
		if ((*command)[command_number].command)
		{
			while ((*command)[command_number].command[i])
			{
				printf("\033[0;31mcommand[%d] = %s\033[0m\n", i, (*command)[command_number].command[i]);
				i++;
			}
		}
		if ((*command)[command_number].heredoc_delimiter)
			printf("heredoc_delimiter = %s\n", *((*command)[command_number].heredoc_delimiter));
		if ((*command)[command_number].redirect_in)
			printf("redirect_in = %s\n", *((*command)[command_number].redirect_in));
		if ((*command)[command_number].redirect_out)
			printf("redirect_out = %s\n", *((*command)[command_number].redirect_out));
		if ((*command)[command_number].redirect_append)
			printf("redirect_append = %s\n", *((*command)[command_number].redirect_append));
		if ((*command)[command_number].redirect_heredoc)
			printf("heredoc_bool = %d\n", (*command)[command_number].redirect_heredoc);
		command_number++;
		printf("\n");
	}	
}

static void get_number_of_pipes(t_main *main)
{
	int i;

	i = 0;
	main->num_of_pipes = 0;
	while (main->split_input[i])
		if (main->split_input[i++][0] == '|')
			(main->num_of_pipes)++;
}

static void	malloc_commands(t_main *main, t_command **commands, int size)
{
	//printf("size = %d\n", size); //REMOVE
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
		(*commands)[i].command = NULL;
		(*commands)[i].heredoc_delimiter = NULL;
		(*commands)[i].redirect_in = NULL;
		(*commands)[i].redirect_out = NULL;
		(*commands)[i].redirect_heredoc = false;
		(*commands)[i].redirect_append = NULL;
		i++;
	}
}

static void malloc_and_init_commands(t_main *main, t_command **commands)
{
	get_number_of_pipes(main);
	//printf("num_of_pipes = %d\n", main->num_of_pipes); //REMOVE
	malloc_commands(main, commands, main->num_of_pipes + 1);
	initialize_commands(commands, main->num_of_pipes + 1);
}

//If there is a syntax error, does it show before or after heredoc?

int	parsing(t_main *main, t_command **command)
{
	if (!split_input(main))
		return (0);
	print_split_input(main); //REMOVE
	free_and_null_input(main);
	exit_command(main);
	malloc_and_init_commands(main, command);
	tokenize(main, command);
	print_command_structs(main, command); //REMOVE
	free_and_null_split_input(main);

	//Temporary free and null
	free_command_token(main, command); //REMOVE
	free(*command); //REMOVE
	
	return (1);
}
