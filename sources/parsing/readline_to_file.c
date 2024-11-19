/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_to_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:30:12 by eberkowi          #+#    #+#             */
/*   Updated: 2024/11/18 14:30:32 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_malloc_fail_or_signal(t_main *main, t_tokens **tokens
		, int heredoc_fd, char *input)
{
	if (!input && errno != 0)
	{
		print_error("Error: Malloc failed in readline for heredoc\n");
		free_all_and_exit(main, tokens);
	}
	else if (!input)
	{
		close(heredoc_fd);
		return (free_all_for_heredoc(main, tokens));
	}
	return (1);
}

static int	handle_signal_received(t_main *main, t_tokens **tokens
		, int heredoc_fd, char **input)
{
	close (heredoc_fd);
	main->exit_code = g_signal_received;
	g_signal_received = 0;
	free(*input);
	return (free_all_for_heredoc(main, tokens));
}

static void	expand_for_heredoc(t_main *main, t_tokens **tokens, char **input)
{
	if (!expand_quotes_and_vars(main, tokens, input, true))
	{
		print_error("Error: Malloc failed in expand_quotes in heredoc\n");
		free_all_and_exit(main, tokens);
	}
}

static void	write_to_heredoc_and_free_input(char **input, int heredoc_fd)
{
	write(heredoc_fd, *input, ft_strlen(*input));
	write(heredoc_fd, "\n", 1);
	free(*input);
	*input = NULL;
}

int	readline_to_file(t_main *main, t_tokens **tokens, t_redirect_node *temp)
{
	int		heredoc_fd;
	char	*input;

	heredoc_fd = open(temp->name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	activate_heredoc_signals();
	rl_event_hook = event;
	while (1)
	{
		input = readline("> ");
		if (!check_malloc_fail_or_signal(main, tokens, heredoc_fd, input))
			return (0);
		if (g_signal_received)
			return (handle_signal_received(main, tokens, heredoc_fd, &input));
		if (!ft_strncmp(input, temp->delimiter
				, ft_strlen(temp->delimiter) + 1))
		{
			free(input);
			break ;
		}
		if (!temp->delimiter_has_quotes)
			expand_for_heredoc(main, tokens, &input);
		write_to_heredoc_and_free_input(&input, heredoc_fd);
	}
	close(heredoc_fd);
	return (1);
}
