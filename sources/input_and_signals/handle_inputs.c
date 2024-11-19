/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_inputs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:11:12 by eberkowi          #+#    #+#             */
/*   Updated: 2024/11/19 11:28:25 by maheleni         ###   ########.fr       */
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
		main->exit_code = g_signal_received;
		g_signal_received = 0;
		if (*input)
			free(*input);
		return (0);
	}
	if (*input == NULL || **input == '\n' || **input == '\0')
	{
		printf("exit\n");
		//print_error("exit\n");
		return (-1);
	}
	else if (*input && *input[0] == '\0')
		return (0);
	add_history(*input);
	return (1);
}
