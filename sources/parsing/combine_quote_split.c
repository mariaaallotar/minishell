/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine_quote_split.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:52:41 by eberkowi          #+#    #+#             */
/*   Updated: 2024/11/19 10:17:12 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	next_id(t_main *main, char **quote_split)
{
	while (main->id_quote_split < main->quote_split_length)
	{
		if (quote_split[main->id_quote_split])
			return (main->id_quote_split);
		(main->id_quote_split)++;
	}
	return (0);
}

static int	combine_remaining_elements(t_main *main, t_tokens **tokens
		, char ***quote_split, char **str)
{
	char	*temp;

	temp = NULL;
	while (main->id_quote_split < main->num_of_existing_elements)
	{
		temp = ft_strdup(*str);
		if (!temp)
			free_and_exit_combine_elements(main, tokens, quote_split);
		free(*str);
		*str = NULL;
		*str = ft_strjoin(temp, (*quote_split)[next_id(main, *quote_split)]);
		if (!*str)
		{
			print_error("Error: Failed to malloc str in combine quote_split\n");
			free(temp);
			return (0);
		}
		free(temp);
		temp = NULL;
		(main->id_quote_split)++;
	}
	return (1);
}

static int	combine_first_two_elements(t_main *main, char ***quote_split
		, char **str)
{
	char	*temp;

	temp = NULL;
	temp = ft_strdup((*quote_split)[next_id(main, *quote_split)]);
	if (!temp)
	{
		print_error("Error: Failed to malloc temp var in combine_quote_split\n");
		return (0);
	}
	(main->id_quote_split)++;
	*str = ft_strjoin(temp, (*quote_split)[next_id(main, *quote_split)]);
	if (!*str)
	{
		print_error("Error: Failed to malloc str in combine_quote_split\n");
		free(temp);
		return (0);
	}
	free(temp);
	(main->id_quote_split)++;
	return (1);
}

static int	get_num_of_existing(t_main *main, char **quote_split)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (i < main->quote_split_length)
	{
		if (quote_split[i])
			result++;
		i++;
	}
	return (result);
}

int	combine_quote_split(t_main *main, t_tokens **tokens
		, char ***quote_split, char **str)
{
	free(*str);
	*str = NULL;
	main->id_quote_split = 0;
	main->num_of_existing_elements = get_num_of_existing(main, *quote_split);
	if (main->num_of_existing_elements == 0)
		return (1);
	if (main->num_of_existing_elements == 1)
	{
		*str = ft_strdup((*quote_split)[next_id(main, *quote_split)]);
		if (!*str)
		{
			print_error("Error: Failed to malloc str in combine quote_split\n");
			return (0);
		}
		return (1);
	}
	if (!combine_first_two_elements(main, quote_split, str))
		return (0);
	if (!combine_remaining_elements(main, tokens, quote_split, str))
		return (0);
	return (1);
}
