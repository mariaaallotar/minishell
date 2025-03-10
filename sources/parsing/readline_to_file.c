/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_to_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:30:12 by eberkowi          #+#    #+#             */
/*   Updated: 2024/12/05 14:45:33 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static int	check_for_empty_prompt(int fd, char **in)
{
	if (*in && (*in)[0] == '\0')
	{
		free(*in);
		*in = NULL;
		write(fd, "\n", 1);
		return (1);
	}
	return (0);
}

static int	check_for_delimiter(char **in, t_redirect_node *temp)
{
	if (!ft_strncmp(*in, temp->delimiter, ft_strlen(temp->delimiter) + 1))
	{
		free(*in);
		return (1);
	}
	return (0);
}

int	readline_to_file(t_main *main, t_tokens **tokens, t_redirect_node *temp)
{
	char	*in;

	main->fd = open(temp->name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	activate_heredoc_signals();
	rl_event_hook = event;
	while (1)
	{
		in = NULL;
		in = readline("> ");
		if (g_signal_received == 2)
			return (handle_signal_received(main, tokens, main->fd, &in));
		if (in == NULL)
			break ;
		if (!check_malloc_fail_or_signal(main, tokens, main->fd, in))
			return (0);
		if (check_for_delimiter(&in, temp))
			break ;
		if (check_for_empty_prompt(main->fd, &in))
			continue ;
		if (!temp->delimiter_has_quotes)
			expand_for_heredoc(main, tokens, &in);
		write_to_heredoc_and_free_input(&in, main->fd);
	}
	close(main->fd);
	return (1);
}
