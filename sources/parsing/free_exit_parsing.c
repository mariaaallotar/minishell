/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:44:31 by eberkowi          #+#    #+#             */
/*   Updated: 2024/10/23 12:07:37 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_split_and_tokens(t_main *main, t_tokens **tokens)
{
	ft_free_split(&main->split_input);
	free(*tokens);
}

void	free_all_and_exit(t_main *main, t_tokens **tokens)
{
	free_and_null_split_input(main);
	free_token_commands(main, tokens);
	free_token_redirects(main, tokens);
	free(*tokens);
	free_environment(&(main->env_list));
	exit (1);
}

static void	ft_free_split_with_middle_null(char ***arr)
{
	int	i;

	i = 0;
	while ((*arr)[i])
		free((*arr)[i++]);
	i++;
	while ((*arr)[i])
		free((*arr)[i++]);
	free(*arr);
}

void	free_all_and_exit_with_free_split_middle(t_main *main
	, t_tokens **tokens)
{
	ft_free_split_with_middle_null(&main->split_input);
	free_token_commands(main, tokens);
	free_token_redirects(main, tokens);
	free(*tokens);
	free_environment(&(main->env_list));
	exit (1);
}

void	free_and_null_split_input(t_main *main)
{
	if (main->split_input)
	{
		ft_free_split(&main->split_input);
		main->split_input = NULL;
	}
}

void	exit_free_split_element_malloc_failed(t_main *main, int i)
{
	while (i >= 0)
	{
		free(main->split_input[i]);
		i--;
	}
	free(main->split_input);
	free(main->input);
	exit (1);
}

void	free_token_commands(t_main *main, t_tokens **tokens)
{
	int	i;

	i = 0;
	while (i < main->num_of_pipes + 1)
	{
		if ((*tokens)[i].command)
			ft_free_split(&((*tokens)[i].command));
		i++;
	}
}

void	free_token_redirects(t_main *main, t_tokens **tokens)
{
	int				token_number;
	t_redirect_node	*temp;
	t_redirect_node	*temp_next;

	token_number = 0;
	while (token_number < main->num_of_pipes + 1)
	{
		temp = (*tokens)[token_number].infiles;
		while (temp)
		{
			temp_next = temp->next;
			if (temp->type == HEREDOC)
				free(temp->delimiter);
			if (temp->type == INFILE || (temp->type == HEREDOC && temp->name))
				free(temp->name);
			free(temp);
			temp = temp_next;
		}
		temp = (*tokens)[token_number].outfiles;
		while (temp)
		{
			temp_next = temp->next;
			free(temp->name);
			free(temp);
			temp = temp_next;
		}
		token_number++;
	}
}

void	free_and_exit_node_malloc_failed(t_main *main, t_tokens **tokens)
{
	printf("Error: Failed to malloc node for redirect linked list\n");
	ft_free_split(&main->split_input);
	free_token_commands(main, tokens);
	free_token_redirects(main, tokens);
	free(*tokens);
	free_environment(&(main->env_list));
	exit (1);
}

void	free_and_exit_variable_malloc_failed(t_main *main, int i)
{
	while (main->split_input[i])
	{
		free(main->split_input[i]);
		i++;
	}
	ft_free_split(&main->split_input);
	exit (1);
}

void	free_and_exit_quote_malloc(t_main *main, t_tokens **tokens, int token_id, int cmd_id)
{
	int	i;

	i = 1;
	while ((*tokens)[token_id].command[cmd_id + i])
	{
		free((*tokens)[token_id].command[cmd_id + i]);
		i++;
	}
	free_and_null_split_input(main);
	free_token_commands(main, tokens);
	free_token_redirects(main, tokens);
	free(*tokens);
	free_environment(&(main->env_list));
	exit (1);
}

void	free_and_exit_combine_elements(t_main *main, t_tokens **tokens, char ***quote_split)
{
	printf("Error: Failed to malloc temp var for quote_split combine\n");
	ft_free_split(quote_split);
	free_all_and_exit(main, tokens);
}
