/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit_parsing_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:44:31 by eberkowi          #+#    #+#             */
/*   Updated: 2024/11/07 10:36:19 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	// char *message = "Before free_token_redirects\n";
	// write(STDERR_FILENO, message, ft_strlen(message));
	while (token_number < main->num_of_pipes + 1)
	{
		temp = (*tokens)[token_number].redirects;
		while (temp)
		{
			temp_next = temp->next;
			if (temp->type == HEREDOC)
				free(temp->delimiter);
			if (temp->type == INFILE || (temp->type == HEREDOC && temp->name)
				|| temp->type == OUTFILE || temp->type == APPEND)
				free(temp->name);
			free(temp);
			temp = temp_next;
		}
		token_number++;
	}
	// message = "After free_token_redirects\n";
	// write(STDERR_FILENO, message, ft_strlen(message));
}

void	free_and_exit_node_malloc_failed(t_main *main, t_tokens **tokens)
{
	print_error("Error: Failed to malloc node for redirect linked list\n");
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
