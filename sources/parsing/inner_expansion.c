/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inner_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:16:01 by eberkowi          #+#    #+#             */
/*   Updated: 2024/10/28 12:07:21 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	expand_vars_in_quotes_inner(t_main *main, char ***quote_split)
{
	int	i;

	i = 0;
	while ((*quote_split)[i])
	{
		if (!find_var_and_remalloc(main, &(*quote_split)[i]))
		{
			printf("Error: Failed to malloc environment variable in quotes\n");
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
			printf("Error: Failed to malloc str in combine quote_split\n");
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
		{
			printf("Error: Failed to malloc str in combine quote_split\n");
			return (0);
		}
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

int	inner_expansion(t_main *main, char **str)
{
	char	**quote_split;
	
	if (!remove_outside_quotes(str))
		return (0);
	if ((*str)[0] == '\0')
		return (1);
	if (!create_quote_split(*str, &quote_split))
		return (0);
	//PRINT QUOTE_SPLIT REMOVE
	// int id_print = 0;
	// while (quote_split[id_print])
	// {
	// 	printf("inner_quote_split[%d] = %s\n", id_print, quote_split[id_print]);
	// 	id_print++;
	// }
	
	if (!expand_vars_in_quotes_inner(main, &quote_split))
		return (0);
		
	//PRINT QUOTE_SPLIT REMOVE
	// id_print = 0;
	// while (quote_split[id_print])
	// {
	// 	printf("inner_quote_split_after_expand[%d] = %s\n", id_print, quote_split[id_print]);
	// 	id_print++;
	// }

	if (!combine_quote_split_inner(&quote_split, str))
	{
		printf("Error: Failed to malloc temp var for quote_split combine\n");
		ft_free_split(&quote_split);
		return (0);
	}	
	
	ft_free_split(&quote_split);
	return (1);
}
