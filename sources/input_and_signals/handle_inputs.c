/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_inputs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:11:12 by eberkowi          #+#    #+#             */
/*   Updated: 2024/11/29 14:51:16 by eberkowi         ###   ########.fr       */
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
	//BEGIN TEST
	// if (isatty(fileno(stdin)))
	// 	*input = readline("minishell: ");
	// else
	// {
	// 	char *line;
	// 	line = get_next_line(fileno(stdin));
	// 	*input = ft_strtrim(line, "\n");
	// 	free(line);
	// }
	// char *temp = ft_strdup(*input);
	// free(*input);
	// *input = temp;
	//END TEST
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
	{
		free(*input);
		return (0);
	}
	add_history(*input);
	return (1);
}
