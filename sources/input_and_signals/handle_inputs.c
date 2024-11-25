/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_inputs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:11:12 by eberkowi          #+#    #+#             */
/*   Updated: 2024/11/25 12:24:51 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_inputs(char **input, t_main *main)
{
	if (isatty(0))
	{
		activate_readline_signals();
		rl_event_hook = event;
	}
	*input = readline("minishell: ");
	if (g_signal_received)
	{
		main->exit_code = g_signal_received + 128;
		g_signal_received = 0;
		if (*input)
			free(*input);
		return (0);
	}
	if (*input == NULL)
	{
		print_error("exit\n");
		return (-1);
	}
	else if (*input && *input[0] == '\0')
		return (0);
	add_history(*input);
	return (1);
}
