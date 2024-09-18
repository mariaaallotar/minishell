/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_inputs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:11:12 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/18 11:13:41 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	display_prompt_and_wait_for_input(char **input)
{
	*input = readline("minishell: "); //TODO Change to set directly in struct
	if (!*input)
		exit (error_exit_handle_input());
	if (*input)
		add_history(*input);
}

void handle_input(char **input)
{
	display_prompt_and_wait_for_input(input);
	//add_input_to_history(*input);
}
