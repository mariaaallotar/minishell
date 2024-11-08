/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:52:55 by eberkowi          #+#    #+#             */
/*   Updated: 2024/11/07 15:18:45 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	create_filename(char **name, int num_of_heredocs)
{
	char	*heredoc_num;

	heredoc_num = NULL;
	heredoc_num = ft_itoa(num_of_heredocs);
	if (!heredoc_num)
	{
		print_error("Error: Failed to malloc heredoc filename number\n");
		return (0);
	}
	*name = NULL;
	*name = ft_strjoin("heredoc_", heredoc_num);
	if (!*name)
	{
		print_error("Error: Failed to malloc heredoc filename joining\n");
		free(heredoc_num);
		return (0);
	}
	free(heredoc_num);
	return (1);
}

int	event(void)
{
	return (0);
}

static int	readline_to_file(t_main *main, t_tokens **tokens
		, t_redirect_node *temp)
{
	int		heredoc_fd;
	char	*input;
	int		input_len;
	int		delimiter_len;

	delimiter_len = ft_strlen(temp->delimiter);
	heredoc_fd = open(temp->name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	activate_heredoc_signals();
	rl_event_hook = event;
	while (1)
	{
		input = readline("> ");
		if (signal_received)
		{
			close (heredoc_fd);
			main->exit_code = signal_received;
			signal_received = 0;
			return (0);
		}
		if (!input)
		{
			print_error("Error: Malloc failed in readline for heredoc\n");
			free_all_and_exit(main, tokens);
		}
		input_len = ft_strlen(input);
		if (!ft_strncmp(input, temp->delimiter, delimiter_len + 1))
		{
			free(input);
			input = NULL;
			break ;
		}
		if (!temp->delimiter_has_quotes)
		{
			if (!expand_quotes_and_vars(main, tokens, &input, true))
			{
				print_error("Error: Malloc failed in expand_quotes in heredoc\n");
				free(input);
				free_all_and_exit(main, tokens);
			}
		}
		write(heredoc_fd, input, ft_strlen(input));
		write(heredoc_fd, "\n", 1);
		free(input);
		input = NULL;
	}
	close(heredoc_fd);
	return (1);
}

int	create_heredoc(t_main *main, t_tokens **tokens)
{
	int				token_id;
	int				num_of_heredocs;
	t_redirect_node	*temp;

	token_id = 0;
	num_of_heredocs = 0;
	while (token_id <= main->num_of_pipes)
	{
		temp = (*tokens)[token_id].redirects;
		while (temp)
		{
			if (temp->type == HEREDOC)
			{
				if (!create_filename(&temp->name, num_of_heredocs))
					free_all_and_exit(main, tokens);
				if (readline_to_file(main, tokens, temp) == 0)
					return (0);
				num_of_heredocs++;
			}
			temp = temp->next;
		}
		token_id++;
	}
	return (1);
}
