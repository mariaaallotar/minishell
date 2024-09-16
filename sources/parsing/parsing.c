/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:32:36 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/16 14:34:21 by eberkowi         ###   ########.fr       */
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
	main->split_input = malloc(split_length * sizeof(char *));
	if (!main->split_input)
	{
		free(main->input);
		main->input = NULL;
		exit (1);
	}
	printf("split_length = %d\n", split_length); //REMOVE	
}

static void	add_elements_to_split_input(t_main *main)
{
	int i;
	int j;
	int element_length;

	i = 0;
	while (*main->input)
	{
		while (*main->input && (*main->input == ' ' || *main->input == '\t'))
			main->input++;
		if (!*main->input)
			return ;
			j = 0;
		element_length = get_element_length(main->input);
		main->split_input[i] = malloc(element_length + 1);
		while (*main->input && *main->input != ' ' && *main->input != '\t')
		{
			main->split_input[i][j++] = *main->input++;
		}
		main->split_input[i][j] = '\0';
		i++;
	}	
}

static void	mini_split(t_main *main)
{
	malloc_split_input_array(main);
	add_elements_to_split_input(main);

	free(main->input);
	main->input = NULL;
}

void	parsing(t_main *main)
{
	exit_for_testing(main); //REMOVE
	mini_split(main);
	free(main->split_input); // replace with ft_free_split
	//ft_free_split(&main->split_input);
	main->split_input = NULL;
}
