/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elements_to_split_input.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:56:14 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/17 19:52:31 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	get_regular_element_length(char *element)
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

static size_t get_double_quote_element_length(char *element)
{
	size_t result;

	result = 1;
	element++;
	while (*element)
	{
		result++;
		if (*element == '\"')
			return (result);
		element++;
	}
	return (result);
}

static void add_special_character_element(t_main *main, char *input, int *i, int split_index)
{
	//check for << and >>
	if ((input[*i] == '<' && input[*i + 1] == '<') ||
		(input[*i] == '>' && input[*i + 1] == '>'))
	{
		main->split_input[split_index] = malloc(3);
		if (!main->split_input[split_index])
			exit_free_split_element_malloc_failed(main, split_index); //TODO check this memory
		main->split_input[split_index][0] = input[*i];
		main->split_input[split_index][1] = input[*i + 1];
		main->split_input[split_index][3] = '\0';
		*i += 2;
	}
	else
	{
		main->split_input[split_index] = malloc(2);
		if (!main->split_input[split_index])
		exit_free_split_element_malloc_failed(main, split_index); //TODO check this memory
		main->split_input[split_index][0] = input[*i];
		main->split_input[split_index][1] = '\0';
		*i += 1;
	}
}

void	add_elements_to_split_input(t_main *main, char *input)
{
	int i;
	int j;
	int index;
	size_t element_length;

	i = 0;
	index = 0;
	while (input[index])
	{
		//skip spaces and tabs
		while (input[index] && (input[index] == ' ' || input[index] == '\t'))
			index++;

		//Double quotes malloc and add elements -------------------------------
		if (input[index] == '\"')
		{
			//get element length
			element_length = get_double_quote_element_length(input + index);
			
			//check for empty double quotes ""
			if (element_length == 2)
			{
				printf("Error: Empty double quotes \"\""); //TODO replace with actual "" handling
				exit_free_split_element_malloc_failed(main, i - 1); //TODO fix this memory shit
			}

			//malloc space for element
			main->split_input[i] = malloc(element_length + 1);
			if (!main->split_input[i]) //TODO maybe need to double check this works?
				exit_free_split_element_malloc_failed(main, i - 1);

			//put quotes and chars into element
			j = 0;
			while (input[index])
			{
				main->split_input[i][j++] = input[index];
				index++;
				if (input[index] == '\"')
					break ;
			}
			index++;
			main->split_input[i][j] = '\"';
			main->split_input[i][j + 1] = '\0';
		}
		
		//Special characters malloc and add elements--------------------------------
		else if (is_special(input[index]))
			add_special_character_element(main, input, &index, i);

		//Regular words malloc and add elements--------------------------------
		else
		{
			//get element length
			element_length = get_regular_element_length(input + index);

			//stop if at the end of the string
			if (!input[index] || element_length == 0)
			{
				main->split_input[i] = NULL;
				return ;
			}

			//malloc space for element
			main->split_input[i] = malloc(element_length + 1);
			if (!main->split_input[i]) //TODO maybe need to double check this works?
				exit_free_split_element_malloc_failed(main, i - 1);

			//put chars into element
			j = 0;
			while (input[index] && input[index] != ' ' && input[index] != '\t')
			{
				if (is_special(input[index]))
					break ;
				main->split_input[i][j++] = input[index];
				index++;
			}
			main->split_input[i][j] = '\0';
		}
		i++;
	}
	main->split_input[i] = NULL;
}
