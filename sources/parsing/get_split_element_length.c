/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_split_element_length.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:17:24 by eberkowi          #+#    #+#             */
/*   Updated: 2024/10/30 15:58:37 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	len_for_dollar_sign(char *str, int i, size_t *result)
{
	if (str[i + 1] == '?')
	{
		(*result) = 2;
		return ;
	}
	(*result) = 1;
	i++;
	while (ft_isalnum(str[i]) || str[i] == '_')
	{
		(*result)++;
		i++;
	}	
}

static void	len_for_given_quote_type(char *str, int i
		, size_t *result, char quote_type)
{
	(*result) = 1;
	i++;
	while (str[i])
	{
		if (str[i] == quote_type)
		{
			(*result)++;
			return ;
		}
		(*result)++;
		i++;
	}	
}

int	get_split_element_len(char *str, int i)
{
	size_t	result;

	if (str[i] == '$')
		len_for_dollar_sign(str, i, &result);
	else if (str[i] == '\"')
		len_for_given_quote_type(str, i, &result, '\"');
	else if (str[i] == '\'')
		len_for_given_quote_type(str, i, &result, '\'');
	else
	{
		result = 0;
		while (str[i] && str[i] != '$' && str[i] != '\"' && str[i] != '\'')
		{
			result++;
			i++;
		}
	}
	return (result);
}
