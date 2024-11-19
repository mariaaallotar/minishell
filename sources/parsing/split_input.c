/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:19:25 by eberkowi          #+#    #+#             */
/*   Updated: 2024/11/18 13:29:07 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_split_length(char *input)
{
	int	result;

	result = 0;
	while (*input)
	{
		while (*input && (*input == ' ' || *input == '\t'))
			input++;
		if (char_is_special(*input))
		{
			result += 2;
			input++;
		}
		else if (*input)
		{
			input++;
			result++;
		}
		else
			return (result);
	}
	return (result);
}

static int	malloc_split_input_array(t_main *main)
{
	int	split_length;

	split_length = 0;
	if (main->input)
		split_length = get_split_length(main->input);
	if (split_length == 0)
		return (0);
	main->split_input = malloc((split_length + 1) * sizeof(char *));
	if (!main->split_input)
	{
		print_error("Error: Failed to malloc array for split_input\n");
		free(main->input);
		main->input = NULL;
		return (0);
	}
	while (split_length)
	{
		main->split_input[split_length] = NULL;
		split_length--;
	}
	return (1);
}

int	split_input(t_main *main)
{
	if (!malloc_split_input_array(main))
		return (0);
	if (!add_elements_to_split_input(main, main->input))
		return (0);
	return (1);
}
