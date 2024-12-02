/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_quote_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:55:37 by eberkowi          #+#    #+#             */
/*   Updated: 2024/12/02 10:28:57 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_split_in_middle(char ***quote_split, int id_split)
{
	if (id_split < 0)
		return ;
	while ((*quote_split)[id_split])
	{
		free((*quote_split)[id_split]);
		id_split--;
		if (id_split < 0)
			return ;
	}
}

static int	get_quote_split_len(char *str)
{
	int		i;
	int		num_of_vars;
	int		result;

	i = 0;
	num_of_vars = 0;
	while ((str)[i])
	{
		if ((str)[i] == '$')
			num_of_vars++;
		i++;
	}
	i = 0;
	while ((str)[i])
	{
		if ((str)[i] == '\"' || (str)[i] == '\'')
			num_of_vars++;
		i++;
	}
	if (num_of_vars == 1)
		result = 3;
	else
		result = ((num_of_vars - 1) * 2) + 3;
	return (result);
}

static int	malloc_quote_split(char *str, char ***quote_split)
{
	int	i;
	int	quote_split_len;

	quote_split_len = get_quote_split_len(str) + 1;
	*quote_split = NULL;
	*quote_split = malloc(quote_split_len * sizeof(char *));
	if (!*quote_split)
	{
		print_error("Error: Failed to malloc quote_split\n");
		return (0);
	}
	i = quote_split_len;
	while (i > 0)
	{
		(*quote_split)[i - 1] = NULL;
		i--;
	}
	return (quote_split_len);
}

static int	malloc_error_free_and_print(char ***quote_split, int id_split)
{
	print_error("Error: Failed to malloc element in quote_split\n");
	free_split_in_middle(quote_split, id_split - 1);
	free(*quote_split);
	return (0);
}

int	create_quote_split(char *str, char ***quote_split)
{
	int		id_str;
	int		id_split;
	size_t	split_element_len;
	int		quote_split_len;

	quote_split_len = malloc_quote_split(str, quote_split);
	if (!quote_split_len)
		return (0);
	id_str = 0;
	id_split = 0;
	while (str[id_str])
	{
		split_element_len = get_split_element_len(str, id_str);
		(*quote_split)[id_split] = NULL;
		(*quote_split)[id_split] = malloc(split_element_len + 1);
		if (!(*quote_split)[id_split])
			return (malloc_error_free_and_print(quote_split, id_split));
		add_element_to_quote_split(quote_split, str, id_split, id_str);
		id_str += (int)split_element_len;
		id_split++;
	}
	return (quote_split_len);
}
