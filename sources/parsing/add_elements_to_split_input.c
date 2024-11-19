/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elements_to_split_input.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:56:14 by eberkowi          #+#    #+#             */
/*   Updated: 2024/11/08 15:45:40 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_for_bonus_symbols(char *input, int id_input)
{
	if ((input[id_input] == '|' && input[id_input + 1] == '|')
		|| input[id_input] == '&' || input[id_input] == '*')
	{
		print_error("Error: Invalid symbol\n");
		return (1);
	}
	return (0);
}

static size_t	get_length_of_split_input_element(char *input, int id_input)
{
	t_parsing	p;
	size_t		result;

	result = 0;
	p.id_char = 0;
	p.num_of_singles = 0;
	p.num_of_doubles = 0;
	p.inside_singles = false;
	p.inside_doubles = false;
	while (input[id_input])
	{
		if (char_is_space_or_special_and_quotes_are_closed(input[id_input], p))
			break ;
		update_number_of_quotes(input[id_input], &p);
		update_inside_status(&p);
		result++;
		p.id_char++;
		(id_input)++;
	}
	return (result);
}

static void	malloc_element_in_split_input(t_main *main, char *input
		, int id_input, int id_split)
{
	size_t	len_of_element;

	len_of_element = get_length_of_split_input_element(input, id_input);
	main->split_input[id_split] = NULL;
	main->split_input[id_split] = malloc(len_of_element + 1);
	if (!main->split_input[id_split])
	{
		print_error("Error: Failed to malloc element in split_input\n");
		ft_free_split(&main->split_input);
		exit (0);
	}
}

static int	add_regular_or_quote_element(t_main *main, char *input
		, int *id_input, int id_split)
{
	t_parsing	p;

	p.id_char = 0;
	p.num_of_singles = 0;
	p.num_of_doubles = 0;
	p.inside_singles = false;
	p.inside_doubles = false;
	malloc_element_in_split_input(main, input, *id_input, id_split);
	while (input[*id_input])
	{
		if (char_is_space_or_special_and_quotes_are_closed(input[*id_input], p))
			break ;
		update_number_of_quotes(input[*id_input], &p);
		update_inside_status(&p);
		main->split_input[id_split][p.id_char] = input[*id_input];
		p.id_char++;
		(*id_input)++;
	}
	main->split_input[id_split][p.id_char] = '\0';
	if (check_for_unclosed_quotes(p))
		return (0);
	return (1);
}

int	add_elements_to_split_input(t_main *main, char *input)
{
	int	id_split;
	int	id_input;

	id_split = 0;
	id_input = 0;
	while (input[id_input])
	{
		main->split_input[id_split] = NULL;
		skip_spaces_and_tabs(input, &id_input);
		if (check_for_bonus_symbols(input, id_input))
			return (0);
		if (char_is_special(input[id_input]))
			add_special_element(main, input, &id_input, id_split);
		else
		{
			if (!add_regular_or_quote_element(main, input, &id_input, id_split))
				return (0);
		}
		skip_spaces_and_tabs(input, &id_input);
		id_split++;
	}
	return (1);
}
