/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_quotes_and_special_elements.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:39:13 by eberkowi          #+#    #+#             */
/*   Updated: 2024/10/25 14:18:08 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_special_element(t_main *main, char *input, int *i, int split_index)
{
	main->split_input[split_index] = NULL;
	if ((input[*i] == '<' && input[*i + 1] == '<')
		|| (input[*i] == '>' && input[*i + 1] == '>'))
	{
		main->split_input[split_index] = malloc(3);
		if (!main->split_input[split_index])
		{
			printf("Error: Failed to malloc redirect in split_input\n");
			exit_free_split_element_malloc_failed(main, split_index);
		}
		main->split_input[split_index][0] = input[(*i)++];
		main->split_input[split_index][1] = input[(*i)++];
		main->split_input[split_index][2] = '\0';
	}
	else
	{
		main->split_input[split_index] = malloc(2);
		if (!main->split_input[split_index])
		{
			printf("Error: Failed to malloc redirect in split_input\n");
			exit_free_split_element_malloc_failed(main, split_index);
		}
		main->split_input[split_index][0] = input[(*i)++];
		main->split_input[split_index][1] = '\0';
	}
}
