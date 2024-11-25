/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:32:36 by eberkowi          #+#    #+#             */
/*   Updated: 2024/11/25 13:36:25 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	get_number_of_pipes(t_main *main)
{
	int	i;

	i = 0;
	main->num_of_pipes = 0;
	while (main->split_input[i])
		if (main->split_input[i++][0] == '|')
			(main->num_of_pipes)++;
}

static void	malloc_tokens(t_main *main, t_tokens **tokens, int size)
{
	*tokens = malloc((size) * sizeof(t_tokens));
	if (!*tokens)
	{
		print_error("Error: Failed to malloc\n");
		ft_free_split(&main->split_input);
		exit (1);
	}	
}

static void	initialize_tokens(t_tokens **tokens, int size)
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
	malloc_tokens(main, tokens, main->num_of_pipes + 1);
	initialize_tokens(tokens, main->num_of_pipes + 1);
}

int	parsing(t_main *main, t_tokens **tokens)
{
	if (!split_input(main))
		return (0);
	free(main->input);
	main->input = NULL;
	malloc_and_init_tokens(main, tokens);
	if (check_for_pipe_error(main, tokens))
		return (0);
	if (check_for_redirect_error(main))
	{
		free(*tokens);
		return (0);
	}
	tokenize(main, tokens);
	quotes_and_variables(main, tokens);
	if (create_heredoc(main, tokens) == 0)
		return (0);
	return (1);
}
