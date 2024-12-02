/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inner_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:16:01 by eberkowi          #+#    #+#             */
/*   Updated: 2024/12/02 10:29:31 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	expand_vars_in_quotes_inner(t_main *main, char ***quote_split)
{
	int	i;

	i = 0;
	while ((*quote_split)[i])
	{
		if (!find_var_in_env(main, &(*quote_split)[i]))
		{
			print_error("Error: Failed to malloc env variable in quotes\n");
			i++;
			while ((*quote_split)[i])
			{
				free((*quote_split)[i]);
				i++;
			}
			ft_free_split(quote_split);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	get_num_of_elements(char **quote_split, int quote_split_len)
{
	int	i;
	int	result;

	result = 0;
	i = 0;
	while (i < quote_split_len)
	{
		if (quote_split[i])
			result++;
		i++;
	}
	return (result);
}

static int	join_multiple_strs(int quote_split_len, char **str
	, char **quote_split)
{
	int		i;
	char	*temp;

	i = 0;
	while (i < quote_split_len)
	{
		if (quote_split[i])
		{
			temp = ft_strjoin(*str, quote_split[i]);
			if (!temp)
				return (0);
			free(*str);
			*str = NULL;
			*str = ft_strdup(temp);
			free(temp);
			if (!*str)
				return (0);
		}
		i++;
	}
	return (1);
}

static int	combine_quote_split_inner(char **quote_split, char **str
	, int quote_split_len)
{
	free(*str);
	*str = NULL;
	if (!get_num_of_elements(quote_split, quote_split_len))
		return (1);
	*str = ft_strdup("");
	if (!*str)
		return (0);
	if (!join_multiple_strs(quote_split_len, str, quote_split))
		return (0);
	return (1);
}

int	inner_expansion(t_main *main, char **str, bool is_heredoc)
{
	char	**quote_split;
	int		quote_split_len;

	if (!remove_outside_quotes(str))
		return (0);
	if ((*str)[0] == '\0')
		return (1);
	quote_split_len = create_quote_split(*str, &quote_split);
	if (!quote_split_len)
		return (0);
	if (!expand_vars_in_quotes_inner(main, &quote_split))
		return (0);
	if (!combine_quote_split_inner(quote_split, str, quote_split_len))
		return (print_error_and_free_split(quote_split_len, &quote_split));
	if (is_heredoc)
	{
		if (!add_quotes_back_to_str(str, '\"'))
			return (print_error_and_free_split(quote_split_len, &quote_split));
	}
	free_quote_split(quote_split_len, &quote_split);
	return (1);
}
