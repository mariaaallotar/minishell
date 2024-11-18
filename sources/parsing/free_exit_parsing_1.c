/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit_parsing_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:44:31 by eberkowi          #+#    #+#             */
/*   Updated: 2024/11/08 12:24:01 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_all_and_exit(t_main *main, t_tokens **tokens)
{
	free_and_null_split_input(main);
	free_token_commands(main, tokens);
	free_token_redirects(main, tokens);
	free(*tokens);
	free_environment(&(main->env_list));
	exit (1);
}

int	free_all_for_heredoc(t_main *main, t_tokens **tokens)
{
	remove_heredocs(main, tokens);
	free_token_commands(main, tokens);
	free_token_redirects(main, tokens);
	free(*tokens);
	return (0);
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
