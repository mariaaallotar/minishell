/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_quotes_and_special_elements.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:39:13 by eberkowi          #+#    #+#             */
/*   Updated: 2024/11/21 13:29:28 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	size_t len_redirect(char *input, int i)
{
	size_t result;

	result = 0;
	while (input[i] == '<' || input[i] == '>')
	{
		result++;
		i++;
	}
	return (result);
}

void	add_special_element(t_main *main, char *input, int *i, int split_index)
{
	int id_split;		
	
	main->split_input[split_index] = NULL;
	if (input[*i] == '|')
	{
		main->split_input[split_index] = malloc(2);
		if (!main->split_input[split_index])
		{
			print_error("Error: Failed to malloc redirect in split_input\n");
			exit_free_split_element_malloc_failed(main, split_index);
		}
		main->split_input[split_index][0] = input[(*i)++];
		main->split_input[split_index][1] = '\0';
	}
	else
	{
		main->split_input[split_index] = malloc(len_redirect(input, *i) + 1);
		if (!main->split_input[split_index])
		{
			print_error("Error: Failed to malloc redirect in split_input\n");
			exit_free_split_element_malloc_failed(main, split_index);
		}
		id_split = 0;
		while (input[*i] == '<' || input[*i] == '>')
			main->split_input[split_index][id_split++] = input[(*i)++];
		main->split_input[split_index][id_split++] = '\0'; 
	}
}
