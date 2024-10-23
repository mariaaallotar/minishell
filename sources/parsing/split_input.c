/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:19:25 by eberkowi          #+#    #+#             */
/*   Updated: 2024/10/23 10:51:23 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_for_quotes(t_main *main, char **input, char c)
{
	(*input)++;
	if (**input == c)
	{
		free(main->input);
		main->input = NULL;
		printf("Error: Empty quotes\n");
		return (0);
	}
	while (**input != c)
	{
		if (!**input)
		{
			free(main->input);
			main->input = NULL;
			if (c == '\'')
				printf("Error: Unclosed single quotes\n");
			else
				printf("Error: Unclosed double quotes in split\n");
			return (0);
		}
		(*input)++;
	}
	(*input)++;
	return (1);
}

static int	split_length_helper(t_main *main, char **input, int *result)
{
	if (**input == '\'')
	{
		if (!check_for_quotes(main, input, '\''))
			return (0);
	}
	else
	{
		while (**input && **input != ' ' && **input != '\t')
		{
			if (is_special(**input))
			{
				*result += 2;
				(*input)++;
				break ;
			}
			(*input)++;
		}	
	}
	return (1);
}

static int	get_split_length(t_main *main, char *input)
{
	int	result;

	result = 0;
	while (*input)
	{
		while (*input && (*input == ' ' || *input == '\t'))
			input++;
		if (*input)
			result++;
		else
			return (result);
		if (!split_length_helper(main, &input, &result))
			return (0);
	}
	return (result);
}

static int	malloc_split_input_array(t_main *main)
{
	int	split_length;

	split_length = 0;
	if (main->input)
		split_length = get_split_length(main, main->input);
	if (split_length == 0)
		return (0);
	main->split_input = malloc((split_length + 1) * sizeof(char *));
	if (!main->split_input)
	{
		printf("Error: Failed to malloc array for split_input\n");
		free(main->input);
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
	add_elements_to_split_input(main, main->input);
	return (1);
}
