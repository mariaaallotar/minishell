/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elements_to_split_input.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:56:14 by eberkowi          #+#    #+#             */
/*   Updated: 2024/10/21 16:12:16 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	get_regular_element_length(char *element)
{
	size_t	result;

	result = 0;
	while (*element && *element >= 33)
	{
		result++;
		element++;
	}
	return (result);
}

static void	add_regular(t_main *main, char *input, int *id_input, int id_split)
{
	size_t	element_length;
	int		i;

	main->split_input[id_split] = NULL;
	element_length = get_regular_element_length(input + *id_input);
	if (!input[*id_input] || element_length == 0)
		return ;
	main->split_input[id_split] = malloc(element_length + 1);
	if (!main->split_input[id_split])
	{
		printf("Error: Failed to malloc regular element to split input\n");
		exit_free_split_element_malloc_failed(main, id_split - 1);
	}
	i = 0;
	while (input[*id_input] && input[*id_input] != ' '
		&& input[*id_input] != '\t')
	{
		if (is_special(input[*id_input]))
			break ;
		main->split_input[id_split][i++] = input[*id_input];
		(*id_input)++;
	}
	main->split_input[id_split][i] = '\0';
}

//Check for bonus symbols '||' '&' and '*' in the front of an element
static void	bonus_front(t_main *main, char *input, int id_input, int id_split)
{
	if ((input[id_input] == '|' && input[id_input + 1] == '|')
		|| input[id_input] == '&' || input[id_input] == '*')
	{
		printf("Error: Invalid symbol\n");
		exit_free_split_element_malloc_failed(main, id_split - 1);
	}
}

//Check for bonus symbols '||' '&' and '*' in the middle of an element
static void	bonus_middle(t_main *main, char *input, int id_input, int id_split)
{
	while (input[id_input] && input[id_input] != ' '
		&& input[id_input] != '\t')
	{
		if ((input[id_input] == '|' && input[id_input + 1] == '|')
			|| input[id_input] == '&' || input[id_input] == '*')
		{
			printf("Error: Invalid symbol\n");
			exit_free_split_element_malloc_failed(main, id_split - 1);
		}
		id_input++;
	}
}

void	add_elements_to_split_input(t_main *main, char *input)
{
	int	id_split;
	int	id_input;

	id_split = 0;
	id_input = 0;
	while (input[id_input])
	{
		while (input[id_input] && (input[id_input] == ' '
				|| input[id_input] == '\t'))
			id_input++;
		bonus_front(main, input, id_input, id_split);
		if (input[id_input] == '\"')
		{
			printf("do add_double_quotes\n"); //REMOVE
			add_double_quotes(main, input, &id_input, id_split);
		}
		else if (input[id_input] == '\'')
		{
			printf("do add_single_quotes\n"); //REMOVE
			add_single_quotes(main, input, &id_input, id_split);
		}
		else if (is_special(input[id_input]))
		{
			printf("do add_redirect_element\n"); //REMOVE
			add_redirect_element(main, input, &id_input, id_split);
		}
		else
		{
			bonus_middle(main, input, id_input, id_split);
			printf("do add_regular\n"); //REMOVE
			add_regular(main, input, &id_input, id_split);
		}
		id_split++;
	}
}
