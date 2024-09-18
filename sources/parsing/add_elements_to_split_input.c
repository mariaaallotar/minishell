/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elements_to_split_input.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:56:14 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/18 13:01:19 by eberkowi         ###   ########.fr       */
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

static void add_regular_element(t_main *main, char *input, int *id_input, int id_split)
{
	size_t element_length;
	int i;
	
	//get element length
	element_length = get_regular_element_length(input + *id_input);

	//stop if at the end of the string
	if (!input[*id_input] || element_length == 0)
	{
		main->split_input[id_split] = NULL;
		return ;
	}

	//malloc space for element
	main->split_input[id_split] = malloc(element_length + 1);
	if (!main->split_input[id_split]) //TODO maybe need to double check this works?
		exit_free_split_element_malloc_failed(main, id_split - 1);

	//put chars into element
	i = 0;
	while (input[*id_input] && input[*id_input] != ' ' && input[*id_input] != '\t')
	{
		if (is_special(input[*id_input]))
			break ;
		main->split_input[id_split][i++] = input[*id_input];
		(*id_input)++;
	}
	main->split_input[id_split][i] = '\0';
}

void	add_elements_to_split_input(t_main *main, char *input)
{
	int id_split;
	int id_input;

	id_split = 0;
	id_input = 0;
	while (input[id_input])
	{
		while (input[id_input] && (input[id_input] == ' ' || input[id_input] == '\t'))
			id_input++;
		if (input[id_input] == '\"')
			add_double_quotes_element(main, input, &id_input, id_split);
		else if (input[id_input] == '\'')
			add_single_quotes_element(main, input, &id_input, id_split);
		else if (is_special(input[id_input]))
			add_special_character_element(main, input, &id_input, id_split);
		else
			add_regular_element(main, input, &id_input, id_split);
		id_split++;
	}
}
