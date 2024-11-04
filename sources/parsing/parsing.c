/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:32:36 by eberkowi          #+#    #+#             */
/*   Updated: 2024/11/04 14:22:47 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void	print_split_input(t_main *main) //REMOVE
// {
// 	printf("\033[0;33m---SPLIT_INPUT---\033[0m\n");
// 	int i = 0;
// 	while (main->split_input[i])
// 	{
// 		printf("input[%d] = %s\n", i, main->split_input[i]);
// 		i++;
// 	}
// 	printf("\n");
// }

// static void	print_tokens(t_main *main, t_tokens **tokens) //REMOVE
// {
// 	int token_number = 0;
// 	int i = 0;
// 	int j = 0;
// 	t_redirect_node *temp;

// 	while (token_number < main->num_of_pipes + 1)
// 	{
// 		printf("\033[0;32m---COMMAND %d---\033[0m\n", token_number);
// 		i = 0;
// 		if ((*tokens)[token_number].command)
// 		{
// 			while ((*tokens)[token_number].command[i])
// 			{
// 				printf("\033[0;31mcommand[%d] = %s\033[0m\n", i
// 					,(*tokens)[token_number].command[i]);
// 				i++;
// 			}
// 		}
// 		//PRINT INFILES AND HEREDOCS
// 		j = 0;
// 		temp = (*tokens)[token_number].redirects;
// 		while (temp)
// 		{
// 			printf("redirect[%d] name = %s, ", j, temp->name);
// 			if (temp->type == INFILE)
// 				printf("type = INFILE");
// 			if (temp->type == HEREDOC)
// 			{
// 				printf("type = HEREDOC");
// 				printf(", delimiter = %s, ", temp->delimiter);
// 				if (temp->delimiter_has_quotes)
// 					printf("delimiter_has_quotes = true\n");
// 				else
// 					printf("delimiter_has_quotes = false\n");
// 			}
// 			if (temp->type == OUTFILE)
// 				printf("type = OUTFILE\n");
// 			if (temp->type == APPEND)
// 				printf("type = APPEND\n");
// 			printf("\n");
// 			temp = temp->next;
// 			j++;
// 		}
// 		token_number++;
// 		printf("\n");
// 		printf("============================================\n");
// 	}
// }

static void	get_number_of_pipes(t_main *main)
{
	int	i;

	i = 0;
	main->num_of_pipes = 0;
	while (main->split_input[i])
		if (main->split_input[i++][0] == '|')
			(main->num_of_pipes)++;
}

static void	malloc_commands(t_main *main, t_tokens **tokens, int size)
{
	*tokens = malloc((size) * sizeof(t_tokens));
	if (!*tokens)
	{
		printf("Error: Failed to malloc\n");
		ft_free_split(&main->split_input);
		exit (1);
	}	
}

static void	initialize_commands(t_tokens **tokens, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		(*tokens)[i].command = NULL;
		(*tokens)[i].redirects = NULL;
		i++;
	}
}

static void	malloc_and_init_tokens(t_main *main, t_tokens **tokens)
{
	get_number_of_pipes(main);
	malloc_commands(main, tokens, main->num_of_pipes + 1);
	initialize_commands(tokens, main->num_of_pipes + 1);
}

int	parsing(t_main *main, t_tokens **tokens)
{
	if (!split_input(main))
		return (0);
	// print_split_input(main); //REMOVE
	free(main->input);
	malloc_and_init_tokens(main, tokens);
	if (check_for_pipe_error(main, tokens))
		return (0);
	if (check_for_redirect_error(main, tokens))
		return (0);
	tokenize(main, tokens);
	quotes_and_variables(main, tokens);
	if (create_heredoc(main, tokens) == 0)
		return (0);
	// print_tokens(main, tokens); //REMOVE
	return (1);
}
