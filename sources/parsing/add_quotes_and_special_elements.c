/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_quotes_and_special_elements.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:39:13 by eberkowi          #+#    #+#             */
/*   Updated: 2024/10/08 11:19:45 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t get_quote_element_length(char *element, char c)
{
	size_t result;

	result = 1;
	element++;
	while (*element)
	{
		result++;
		if (*element == c)
			return (result);
		element++;
	}
	return (result);
}

void add_redirect_element(t_main *main, char *input, int *i, int split_index)
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
		main->split_input[split_index][2] = '\0';
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

void add_double_quotes_element(t_main *main, char *input, int *id_input, int id_split)
{
	size_t element_length;
	int i;
		
	//get element length
	element_length = get_quote_element_length(input + *id_input, '\"');
	
	//check for empty double quotes ""
	if (element_length == 2)
	{
		printf("Error: Empty double quotes \"\""); //TODO replace with actual "" handling
		exit_free_split_element_malloc_failed(main, id_split - 1); //TODO fix this memory shit
	}

	//malloc space for element
	main->split_input[id_split] = malloc(element_length + 1);
	if (!main->split_input[id_split]) //TODO maybe need to double check this works?
		exit_free_split_element_malloc_failed(main, id_split - 1);

	//put quotes and chars into element
	i = 0;
	while (input[*id_input])
	{
		main->split_input[id_split][i++] = input[*id_input];
		(*id_input)++;
		if (input[*id_input] == '\"')
			break ;
	}
	(*id_input)++;
	main->split_input[id_split][i] = '\"';
	main->split_input[id_split][i + 1] = '\0';
}

void add_single_quotes_element(t_main *main, char *input, int *id_input, int id_split)
{
	size_t element_length;
	int i;
		
	//get element length
	element_length = get_quote_element_length(input + *id_input, '\'');
	
	//check for empty single quotes ''
	if (element_length == 2)
	{
		printf("Error: Empty single quotes \'\'"); //TODO replace with actual "" handling
		exit_free_split_element_malloc_failed(main, id_split - 1); //TODO fix this memory shit
	}

	//malloc space for element
	main->split_input[id_split] = malloc(element_length + 1);
	if (!main->split_input[id_split]) //TODO maybe need to double check this works?
		exit_free_split_element_malloc_failed(main, id_split - 1);

	//put quotes and chars into element
	i = 0;
	while (input[*id_input])
	{
		main->split_input[id_split][i++] = input[*id_input];
		(*id_input)++;
		if (input[*id_input] == '\'')
			break ;
	}
	(*id_input)++;
	main->split_input[id_split][i] = '\'';
	main->split_input[id_split][i + 1] = '\0';
}
