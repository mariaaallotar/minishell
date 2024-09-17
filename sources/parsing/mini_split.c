/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:19:25 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/17 12:26:05 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


//Left Off here trying to add spaces for symbols, but first need to skip over double-quotes
//currently exiting mistakenly
static int	get_split_length(t_main *main, char *input)
{
	int result;

	result = 0;
	while (*input)
	{
		while (*input && (*input == ' ' || *input == '\t'))
			input++;
		if (*input)
			result++;
		else
			return (result);
		if (*input == '\"')
		{
			input++;
			while (*input && *input != '\"')
			{
				if (*input)
				{
					free(main->input);
					exit (1); //TODO printf message for unclosed double quote
				}	
			}
			input++;
		}
		else
			while (*input && *input != ' ' && *input != '\t')
				input++;
	}
	return (result);
}

static void	malloc_split_input_array(t_main *main)
{
	int split_length;
	
	if (main->input)
		split_length = get_split_length(main, main->input);
	else
		return ;
	main->split_input = malloc((split_length + 1) * sizeof(char *));
	if (!main->split_input)
	{
		free(main->input);
		exit (1);
	}
	while (split_length)
	{
		main->split_input[split_length] =  NULL;
		split_length--;
	}
}

void	mini_split(t_main *main)
{
	malloc_split_input_array(main);
	add_elements_to_split_input(main, main->input);
}
