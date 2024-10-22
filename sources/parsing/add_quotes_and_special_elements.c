/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_quotes_and_special_elements.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:39:13 by eberkowi          #+#    #+#             */
/*   Updated: 2024/10/22 10:53:26 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	get_single_quote_length(char *element, char c)
{
	size_t	result;

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

// static size_t	get_double_quote_length(char *element)
// {
// 	size_t	result;

// 	result = 1;
// 	element++;
// 	while (*element)
// 	{
// 		result++;
// 		if (!*element || *element == ' ' || *element == '\t')
// 			return (result);
// 		element++;
// 	}
// 	return (result);
// }

void	add_redirect_element(t_main *main, char *input, int *i, int split_index)
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

static void check_for_odd_number_of_double_quotes(t_main *main, char *str)
{
	int num_of_quotes;
	int i;

	i = 0;
	num_of_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			num_of_quotes++;
		i++;
	}
	if (num_of_quotes % 2 != 0)
	{
		printf("Error: Unclosed double quotes\n");
		free(main->input);
		ft_free_split(&main->split_input);
		exit (1);
	}
}

void malloc_double_quotes(t_main *main, char *input, int id_input, int id_spl)
{
	size_t	element_length;

	element_length = 1;
	id_input++;
	while (input[id_input])
	{
		if (input[id_input] == '\"' && (input[id_input + 1] == ' ' 
			|| input[id_input + 1] == '\t' || !input[id_input + 1]))
		{
			element_length++;
			break ;
		}
		element_length++;
		id_input++;
	}
	main->split_input[id_spl] = NULL;
	main->split_input[id_spl] = malloc(element_length + 1);
	if (!main->split_input[id_spl])
	{
		printf("Error: Failed to malloc double-quote element in split\n");
		exit_free_split_element_malloc_failed(main, id_spl - 1);
	}
}

void add_double_quotes(t_main *main, char *input, int *id_input, int id_spl)
{
	int i;

	i = 0;
	malloc_double_quotes(main, input, *id_input, id_spl);
	main->split_input[id_spl][i++] = '\"';
	(*id_input)++;
	while (input[*id_input])
	{
		if (input[*id_input] == '\"' && (input[*id_input + 1] == ' ' 
			|| input[*id_input + 1] == '\t' || !input[*id_input + 1]))
		{
			main->split_input[id_spl][i++] = input[*id_input];
			(*id_input)++;
			break ;
		}
		main->split_input[id_spl][i++] = input[*id_input];
		(*id_input)++;
	}
	main->split_input[id_spl][i] = '\0';
	check_for_odd_number_of_double_quotes(main, main->split_input[id_spl]);
}

// void	add_double_quotes(t_main *main, char *input, int *id_input, int id_spl)
// {
// 	size_t	element_length;
// 	int		i;

// 	//element_length = get_single_quote_length(input + *id_input, '\"');
// 	element_length = get_double_quote_length(input + *id_input);
// 	main->split_input[id_spl] = NULL;
// 	main->split_input[id_spl] = malloc(element_length + 1);
// 	if (!main->split_input[id_spl])
// 	{
// 		printf("Error: Failed to malloc double-quote element in tokens\n");
// 		exit_free_split_element_malloc_failed(main, id_spl - 1);
// 	}
// 	i = 0;
// 	while (input[*id_input])
// 	{
// 		main->split_input[id_spl][i++] = input[*id_input];
// 		(*id_input)++;
// 		//if (input[*id_input] == '\"')
// 		if (input[*id_input] == ' ' || input[*id_input] == '\t')
// 			break ;
// 	}
// 	(*id_input)++;
// 	//main->split_input[id_spl][i] = '\"';
// 	//main->split_input[id_spl][i + 1] = '\0';
// 	main->split_input[id_spl][i] = '\0';
// }

void	add_single_quotes(t_main *main, char *input, int *id_input, int id_spl)
{
	size_t	element_length;
	int		i;

	element_length = get_single_quote_length(input + *id_input, '\'');
	main->split_input[id_spl] = NULL;
	main->split_input[id_spl] = malloc(element_length + 1);
	if (!main->split_input[id_spl])
	{
		printf("Error: Failed to malloc single-quote element in tokens\n");
		exit_free_split_element_malloc_failed(main, id_spl - 1);
	}
	i = 0;
	while (input[*id_input])
	{
		main->split_input[id_spl][i++] = input[*id_input];
		(*id_input)++;
		if (input[*id_input] == '\'')
			break ;
	}
	(*id_input)++;
	main->split_input[id_spl][i] = '\'';
	main->split_input[id_spl][i + 1] = '\0';
}
