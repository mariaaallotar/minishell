/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_to_file_helper.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:03:19 by eberkowi          #+#    #+#             */
/*   Updated: 2024/11/19 10:32:22 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_malloc_fail_or_signal(t_main *main, t_tokens **tokens
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

int	handle_signal_received(t_main *main, t_tokens **tokens
		, int heredoc_fd, char **input)
{
	close (heredoc_fd);
	main->exit_code = signal_received;
	signal_received = 0;
	free(*input);
	return (free_all_for_heredoc(main, tokens));
}
