/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:32:36 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/16 15:29:59 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void exit_for_testing(t_main *main) //REMOVE
{
	if (!ft_strncmp("exit", main->input, 4))
	{
		free(main->input);
		exit (1);	
	}
}

static int	get_split_length(char *input)
{
	int result;

	result = 0;
	while (*input)
	{
		while (*input && (*input == ' ' || *input == '\t'))
			input++;
		if (*input && *input >= 33)
			result++;	
		while (*input && *input != ' ' && *input != '\t')
			input++;
	}
	return (result);
}

static void	malloc_split_input_array(t_main *main)
{
	int split_length;
	
	if (main->input)
		split_length = get_split_length(main->input);
	else
		return ;
	main->split_input = malloc((split_length + 1) * sizeof(char *));
	if (!main->split_input)
	{
		free(main->input);
		main->input = NULL;
		exit (1);
	}
	//printf("split_length = %d\n", split_length); //REMOVE	
}

static void	exit_split_element_malloc_failed(t_main *main, int i)
{
	while (i >= 0)
	{
		free(main->split_input[i]);
		i--;
	}
	free(main->split_input);
	exit (1);
}

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

static void	add_elements_to_split_input(t_main *main)
{
	int i;
	int j;
	size_t element_length;

	i = 0;
	while (*main->input)
	{
		while (*main->input && (*main->input == ' ' || *main->input == '\t'))
			main->input++;
		j = 0;
		element_length = get_element_length(main->input);
		//printf("element %d length = %zu\n", i, element_length); //REMOVE
		if (!*main->input || element_length == 0)
		{
			main->split_input[i] = NULL;
			return ;
		}	
		main->split_input[i] = malloc(element_length + 1);
		if (!main->split_input[i])
			exit_split_element_malloc_failed(main, i - 1);
		while (*main->input && *main->input != ' ' && *main->input != '\t')
		{
			main->split_input[i][j++] = *main->input;
			main->input++;
		}
		main->split_input[i][j] = '\0';
		//printf("element %d  str = %s\n", i, main->split_input[i]);
		i++;
	}
	main->split_input[i] = NULL;
}

static void	mini_split(t_main *main)
{
	malloc_split_input_array(main);
	add_elements_to_split_input(main);
}

void	parsing(t_main *main)
{
	exit_for_testing(main); //REMOVE
	mini_split(main);

	int i = 0;
	while (main->split_input[i])
	{
		printf("index %d = %s\n", i, main->split_input[i]);
		i++;
	}
	
	if (*main->input)
	{
		free(main->input);
		main->input = NULL;
	}	
	ft_free_split(&main->split_input);
	main->split_input = NULL;
}
