/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_inputs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:11:12 by eberkowi          #+#    #+#             */
/*   Updated: 2024/10/28 14:49:16 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//Left off here, newlineand new prompt when no prompt!
//It's the enviroment ! not fgreeing the env

// static int	display_prompt_and_wait_for_input(char **input)
// {
// 	*input = readline("minishell: ");
// 	if (*input == NULL)
// 		return (-1);
// 	if (*input && *input[0] == '\0')
// 		return (0);
// 	return (1);
// }

int	handle_inputs(char **input)
{
	*input = readline("minishell: ");
	if (*input == NULL)
	{
		printf("exit\n");
		return (-1);
	}
	else if (*input && *input[0] == '\0')
		return (0);
	add_history(*input);
	return (1);
}
