/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:59:47 by eberkowi          #+#    #+#             */
/*   Updated: 2024/11/06 11:55:35 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_for_outside_quotes(char *str, char *quote_type)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	i--;
	if (str[0] == '\"' && str[i] == '\"')
	{
		if (quote_type)
			*quote_type = '\"';
		return (1);
	}
	if (str[0] == '\'' && str[i] == '\'')
	{
		if (quote_type)
			*quote_type = '\'';
		return (1);
	}
	return (0);
}

int	add_quotes_back_to_str(char **str, char quote_type)
{
	size_t	add_quote_len;
	size_t	i;
	char	*temp;

	temp = ft_strdup(*str);
	free(*str);
	*str = NULL;
	add_quote_len = ft_strlen(temp) + 3;
	*str = malloc(add_quote_len);
	if (!*str)
	{
		free(temp);
		return (0);
	}
	(*str)[0] = quote_type;
	i = 1;
	while (i < add_quote_len - 2)
	{
		(*str)[i] = temp[i - 1];
		i++;
	}
	(*str)[i++] = quote_type;
	(*str)[i] = '\0';
	free(temp);
	return (1);
}

int	check_for_heredoc_quotes(char **str, bool is_heredoc
		, char quote_type, char ***quote_split)
{
	if (!str)
		return (1);
	if (is_heredoc && quote_type != '\0')
	{
		if (!add_quotes_back_to_str(str, quote_type))
		{
			printf("Error: Failed to malloc add-outside-quotes\n");
			ft_free_split(quote_split);
			return (0);
		}
	}
	return (1);
}

int	remove_outside_quotes(char **str)
{
	size_t	remove_quote_len;
	size_t	i;
	char	*temp;

	temp = ft_strdup(*str);
	free(*str);
	*str = NULL;
	remove_quote_len = ft_strlen(temp) - 1;
	*str = malloc(remove_quote_len);
	if (!*str)
	{
		printf("Error: Failed to malloc remove-outside-quotes\n");
		free(temp);
		return (0);
	}
	i = 0;
	while (i < remove_quote_len - 1)
	{
		(*str)[i] = temp[i + 1];
		i++;
	}
	(*str)[i] = '\0';
	free(temp);
	return (1);
}
