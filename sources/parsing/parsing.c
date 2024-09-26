/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:32:36 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/26 16:51:20 by eberkowi         ###   ########.fr       */
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

static void print_command_structs(t_main *main, t_tokens **tokens) //REMOVE
{
	int command_number = 0;
	int i = 0;
	while (command_number < main->num_of_pipes + 1)
	{
		printf("\033[0;32m---COMMAND %d---\033[0m\n", command_number);
		i = 0;
		if ((*tokens)[command_number].command)
		{
			while ((*tokens)[command_number].command[i])
			{
				printf("\033[0;31mcommand[%d] = %s\033[0m\n", i, (*tokens)[command_number].command[i]);
				i++;
			}
		}
		if ((*tokens)[command_number].heredoc_delimiter)
			printf("heredoc_delimiter = %s\n", *((*tokens)[command_number].heredoc_delimiter));
		if ((*tokens)[command_number].redirect_in)
			printf("redirect_in = %s\n", *((*tokens)[command_number].redirect_in));
		if ((*tokens)[command_number].redirect_out)
			printf("redirect_out = %s\n", *((*tokens)[command_number].redirect_out));
		if ((*tokens)[command_number].redirect_append)
			printf("redirect_append = %s\n", *((*tokens)[command_number].redirect_append));
		if ((*tokens)[command_number].redirect_heredoc)
			printf("heredoc_bool = %d\n", (*tokens)[command_number].redirect_heredoc);
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

static void	malloc_commands(t_main *main, t_tokens **tokens, int size)
{
	//printf("size = %d\n", size); //REMOVE
	*tokens = malloc((size) * sizeof(t_tokens));
	if (!*tokens)
	{
		ft_free_split(&main->split_input);
		printf("Error: Failed to malloc\n");
		exit (1);
	}	
}

static void	initialize_commands(t_tokens **tokens, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		(*tokens)[i].command = NULL;
		(*tokens)[i].heredoc_delimiter = NULL;
		(*tokens)[i].redirect_in = NULL;
		(*tokens)[i].redirect_out = NULL;
		(*tokens)[i].redirect_heredoc = false;
		(*tokens)[i].redirect_append = NULL;
		i++;
	}
}

static void malloc_and_init_tokens(t_main *main, t_tokens **tokens)
{
	get_number_of_pipes(main);
	//printf("num_of_pipes = %d\n", main->num_of_pipes); //REMOVE
	malloc_commands(main, tokens, main->num_of_pipes + 1);
	initialize_commands(tokens, main->num_of_pipes + 1);
}

int	parsing(t_main *main, t_tokens **tokens)
{
	if (!split_input(main))
		return (0);
	print_split_input(main); //REMOVE
	free_and_null_input(main);
	exit_command(main);
	expand_variables(main);
	malloc_and_init_tokens(main, tokens);
	tokenize(main, tokens);
	print_command_structs(main, tokens); //REMOVE
	free_and_null_split_input(main);

	//Temporary free and null
	free_command_token(main, tokens); //REMOVE
	free(*tokens); //REMOVE
	
	return (1);
}
