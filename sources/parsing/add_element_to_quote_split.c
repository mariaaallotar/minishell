/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_element_to_quote_split.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:31:07 by eberkowi          #+#    #+#             */
/*   Updated: 2024/11/01 14:49:31 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	add_non_var_element(char ***quote_split, char *str
		, int id_split, int id_str)
{
	int	i;

	i = 0;
	while (str[id_str] && str[id_str] != '$'
		&& str[id_str] != '\"' && str[id_str] != '\'')
	{
		(*quote_split)[id_split][i] = str[id_str];
		id_str++;
		i++;
	}
	return (i);
}

static int	add_double_quote_element(char ***quote_split, char *str
		, int id_split, int id_str)
{
	int	i;

	(*quote_split)[id_split][0] = str[id_str];
	i = 1;
	id_str++;
	while (str[id_str])
	{
		(*quote_split)[id_split][i] = str[id_str];
		if (str[id_str] == '\"')
		{
			i++;
			return (i);
		}
		id_str++;
		i++;
	}
	return (i);
}

static int	add_single_quote_element(char ***quote_split, char *str
		, int id_split, int id_str)
{
	int	i;

	(*quote_split)[id_split][0] = str[id_str];
	i = 1;
	id_str++;
	while (str[id_str])
	{
		(*quote_split)[id_split][i] = str[id_str];
		if (str[id_str] == '\'')
		{
			i++;
			return (i);
		}
		id_str++;
		i++;
	}
	return (i);
}

static int	add_var_element(char ***quote_split, char *str
		, int id_split, int id_str)
{
	int	i;

	i = 0;
	(*quote_split)[id_split][i] = '$';
	if (str[id_str + 1] == '?')
	{
		(*quote_split)[id_split][i + 1] = '?';
		return (2);
	}
	i++;
	id_str++;
	while (ft_isalnum(str[id_str]) || str[id_str] == '_')
	{
		(*quote_split)[id_split][i] = str[id_str];
		id_str++;
		i++;
	}
	return (i);
}

void	add_element_to_quote_split(char ***quote_split, char *str
		, int id_split, int id_str)
{
	int	i;

	i = 0;
	if (str[id_str] == '$')
		i += add_var_element(quote_split, str, id_split, id_str);
	else if (str[id_str] == '\"')
		i += add_double_quote_element(quote_split, str, id_split, id_str);
	else if (str[id_str] == '\'')
		i += add_single_quote_element(quote_split, str, id_split, id_str);
	else
		i += add_non_var_element(quote_split, str, id_split, id_str);
	(*quote_split)[id_split][i] = '\0';
}
