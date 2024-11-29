/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inner_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:16:01 by eberkowi          #+#    #+#             */
/*   Updated: 2024/11/29 11:42:59 by eberkowi         ###   ########.fr       */
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

static int	combine_remaining_elements_inner(char ***quote_split, char **str)
{
	int		i;
	char	*temp;

	i = 2;
	temp = NULL;
	while ((*quote_split)[i])
	{
		temp = ft_strdup(*str);
		if (!temp)
			return (0);
		free(*str);
		*str = NULL;
		*str = ft_strjoin(temp, (*quote_split)[i]);
		if (!*str)
		{
			free(temp);
			return (0);
		}
		free(temp);
		temp = NULL;
		i++;
	}
	return (1);
}

static int	combine_quote_split_inner(char ***quote_split, char **str)
{
	free(*str);
	*str = NULL;
	if (!(*quote_split)[1])
	{
		*str = ft_strdup((*quote_split)[0]);
		if (!*str)
			return (0);
		return (1);
	}
	else
		*str = ft_strjoin((*quote_split)[0], (*quote_split)[1]);
	if (!*str)
		return (0);
	if (!combine_remaining_elements_inner(quote_split, str))
		return (0);
	return (1);
}

static int	print_error_and_free_split(int len, char ***quote_split)
{
	print_error("Error: Failed to malloc in inner_expansion\n");
	free_quote_split(len, quote_split);
	return (0);
}

// static void print_quote_split(char **quote_split)
// {
// 	printf("\033[0;34m---QUOTE SPLIT ---\033[0m\n");
// 	int i = 0;
// 	while (quote_split[i])
// 	{
// 		printf("quote_split[%d] = %s\n", i, quote_split[i]);
// 		i++;
// 	}
// 	printf("\n");
// }

int	inner_expansion(t_main *main, char **str, bool is_heredoc)
{
	char	**quote_split;
	int		quote_split_len;

	if (!remove_outside_quotes(str))
		return (0);
	if ((*str)[0] == '\0')
		return (1);
	quote_split_len = create_quote_split(*str, &quote_split);
	// printf("INNER BEFORE EXPAND\n"); //REMOVE
	// print_quote_split(quote_split); //REMOVE
	if (!quote_split_len)
		return (0);
	if (!expand_vars_in_quotes_inner(main, &quote_split))
		return (0);
	// printf("INNER AFTER EXPAND\n"); //REMOVE
	// print_quote_split(quote_split); //REMOVE
	if (!combine_quote_split_inner(&quote_split, str))
		return (print_error_and_free_split(quote_split_len, &quote_split));
	if (is_heredoc)
	{
		if (!add_quotes_back_to_str(str, '\"'))
			return (print_error_and_free_split(quote_split_len, &quote_split));
	}
	free_quote_split(quote_split_len, &quote_split);
	return (1);
}
