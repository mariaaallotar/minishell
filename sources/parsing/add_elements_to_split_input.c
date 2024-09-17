/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elements_to_split_input.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:56:14 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/17 11:58:32 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	get_element_length(char *element)
{
	size_t result;

	result = 0;
	while (*element && *element >= 33)
	{
		result++;
		element++;
	}
	return (result);
}

void	add_elements_to_split_input(t_main *main, char *input)
{
	int i;
	int j;
	size_t element_length;

	i = 0;
	while (*input)
	{
		while (*input && (*input == ' ' || *input == '\t'))
			input++;
		element_length = get_element_length(input);
		if (!*input || element_length == 0)
		{
			main->split_input[i] = NULL;
			return ;
		}
		main->split_input[i] = malloc(element_length + 1);
		if (!main->split_input[i]) //maybe need to double check this works?
			exit_free_split_element_malloc_failed(main, i - 1);
		j = 0;
		while (*input && *input != ' ' && *input != '\t')
		{
			main->split_input[i][j++] = *input;
			input++;
		}
		main->split_input[i][j] = '\0';
		i++;
	}
	main->split_input[i] = NULL;
}
