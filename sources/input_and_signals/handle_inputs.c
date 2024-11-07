/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_inputs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:11:12 by eberkowi          #+#    #+#             */
/*   Updated: 2024/11/05 11:55:55 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_inputs(char **input)
{
	// char	*message;

	activate_readline_signals();
	*input = readline("@minishell: ");
	if (*input == NULL)
	{
		// message = "exit\n";
		// write(STDERR_FILENO, message, ft_strlen(message));
		printf("exit\n");
		return (-1);
	}
	else if (*input && *input[0] == '\0')
		return (0);
	add_history(*input);
	return (1);
}
