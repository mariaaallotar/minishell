/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_expansion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:29:55 by eberkowi          #+#    #+#             */
/*   Updated: 2024/10/21 14:41:30 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int check_for_no_vars(char **str)
{
	int i;
	
	i = 0;
	while ((*str)[i] && (*str)[i] != ' ' && (*str)[i] != '\t')
	{
		if ((*str)[i] == '$')
			return (0);
		i++;
	}
	return (1);
}

static int remove_outside_quotes(char **str)
{
	size_t remove_quote_len;
	size_t i;
	char *temp;

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

static int get_quote_split_len(char *str)
{
	int i;
	int num_of_vars;
	size_t result;
	
	i = 0;
	num_of_vars = 0;
	while ((str)[i] && (str)[i] != ' ' && (str)[i] != '\t')
	{
		if ((str)[i] == '$')
			num_of_vars++;
		i++;
	}
	if (num_of_vars == 1)
		result = 3;
	else
		result = ((num_of_vars - 1) * 2) + 3;
	return (result);	
}

static int malloc_quote_split(char *str, char ***quote_split)
{
	size_t quote_split_len;

	quote_split_len = get_quote_split_len(str) + 1;
	*quote_split = NULL;
	*quote_split = malloc(quote_split_len * sizeof(char *));
	if (!*quote_split)
		return (0);
	while (quote_split_len)
	{
		(*quote_split)[quote_split_len - 1] = NULL;
		quote_split_len--;
	}
	return (1);
}

static int get_split_element_len(char *str, int i)
{
	size_t result;

	if (str[i] == '$')
	{
		result = 1;
		i++;
		while (ft_isalnum(str[i]) || str[i] == '_')
		{
			result++;
			i++;
		}
	}
	else
	{
		result = 0;
		while (str[i] && str[i] != '$')
		{
			result++;
			i++;
		}
	}
	return (result);
}

static void free_split_in_middle(char ***quote_split, int id_split)
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

static void add_element_to_quote_split(char ***quote_split, char *str, int id_split, int id_str)
{
	int i;
	i = 0;
	if (str[id_str] == '$')
	{
		(*quote_split)[id_split][i] = '$';
		i++;
		id_str++;
		while (ft_isalnum(str[id_str]) || str[id_str] == '_')
		{
			(*quote_split)[id_split][i] = str[id_str];
			id_str++;
			i++;
		}
	}
	else
	{
		while (str[id_str] && str[id_str] != '$')
		{
			(*quote_split)[id_split][i] = str[id_str];
			id_str++;
			i++;
		}
	}
	(*quote_split)[id_split][i] = '\0';
}

static int create_quote_split(char *str, char ***quote_split)
{
	int id_str;
	int id_split;
	size_t split_element_len;
	
	if (!malloc_quote_split(str, quote_split))
		return (0);
	id_str = 0;
	id_split = 0;
	while (str[id_str])
	{
		split_element_len = get_split_element_len(str, id_str);
		(*quote_split)[id_split] = malloc(split_element_len + 1);
		if (!(*quote_split)[id_split])
		{
			printf("Error: Failed to malloc element in quote_split\n");
			free_split_in_middle(quote_split, id_split - 1);
			free(*quote_split);
			return (0);
		}
		add_element_to_quote_split(quote_split, str, id_split, id_str);
		id_str += (int)split_element_len;
		id_split++;
	}
	return (1);
}

static void expand_vars_in_quotes(t_main *main, t_tokens **tokens, char ***quote_split)
{
	int i;

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
			free_all_and_exit(main, tokens);
		}
		i++;
	}	
}

static int combine_quote_split(t_main *main, t_tokens **tokens, char ***quote_split, char **str)
{
	int i;
	char *temp;

	temp = NULL;
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
	i = 2;
	while ((*quote_split)[i])
	{
		temp = ft_strdup(*str);
		if (!temp)
		{
			printf("Error: Failed to malloc temp var for quote_split combine\n");
			ft_free_split(quote_split);
			free_all_and_exit(main, tokens);
		}
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

int expand_quotes_and_vars(t_main *main, t_tokens **tokens, char **str)
{
	char **quote_split;

	if ((*str)[0] == '\'')
	{
		if (!remove_outside_quotes(str))
			return (0);
		return (1);
	}
	else if ((*str)[0] == '\"')
		if (!remove_outside_quotes(str))
			return (0);
	if (check_for_no_vars(str))
		return (1);
	if (!create_quote_split(*str, &quote_split))
		return (0);
	expand_vars_in_quotes(main, tokens, &quote_split);
	if (!combine_quote_split(main ,tokens, &quote_split, str))
	{
		ft_free_split(&quote_split);
		return (0);
	}
	ft_free_split(&quote_split);
	return (1);
}
