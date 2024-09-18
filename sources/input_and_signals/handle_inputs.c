/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_inputs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:11:12 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/18 13:49:28 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	display_prompt_and_wait_for_input(char **input)
{
	*input = readline("minishell: ");
	if (!*input)
		exit (error_exit_handle_input());
}

void handle_inputs(char **input)
{
	display_prompt_and_wait_for_input(input);
	if (*input)
		add_history(*input);
}
