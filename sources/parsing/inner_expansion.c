/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inner_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:16:01 by eberkowi          #+#    #+#             */
/*   Updated: 2024/11/26 10:22:41 by eberkowi         ###   ########.fr       */
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

static void	print_error_and_free_split(char ***quote_split)
{
	print_error("Error: Failed to malloc in inner_expansion\n");
	ft_free_split(quote_split);
}

int	inner_expansion(t_main *main, char **str, bool is_heredoc)
{
	char	**quote_split;

	if (!remove_outside_quotes(str))
		return (0);
	if ((*str)[0] == '\0')
		return (1);
	if (!create_quote_split(*str, &quote_split))
		return (0);
	if (!expand_vars_in_quotes_inner(main, &quote_split))
		return (0);
	if (!combine_quote_split_inner(&quote_split, str))
	{
		print_error_and_free_split(&quote_split);
		return (0);
	}	
	if (is_heredoc)
	{
		if (!add_quotes_back_to_str(str, '\"'))
		{
			print_error_and_free_split(&quote_split);
			return (0);
		}
	}
	ft_free_split(&quote_split);
	return (1);
}
